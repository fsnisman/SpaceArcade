#include "LevelMap.h"
#include "PlayerShipPawn.h"

ALevelMap::ALevelMap()
{
	PrimaryActorTick.bCanEverTick = true;

	//=========================
	// Create Static Mesh 
	//=========================

	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = MapMesh;

	//=========================
	// Create Effect
	//=========================

	Partical = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Wave Effect"));
	Partical->SetupAttachment(MapMesh);

	//=========================
	// Create HitCollider 
	//=========================

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(MapMesh);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ALevelMap::OnMeshOverlapBegin);

	//=========================
	// Create Spawn Arrow 
	//=========================

	ArrowSpawnMapOne = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point One"));
	ArrowSpawnMapOne->SetupAttachment(MapMesh);
}

void ALevelMap::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeRange);
}

void ALevelMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelMap::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckSpawn)
	{
		return;
	}

	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (playerShip != OtherActor)
	{
		return;
	}
	else
	{
		CheckSpawn = true;

		ALevelMap* LevelMap = GetWorld()->SpawnActor<ALevelMap>(LevelMapClass, ArrowSpawnMapOne->GetComponentLocation(), ArrowSpawnMapOne->GetComponentRotation() + FRotator(0, 0, 0));
	}
}

