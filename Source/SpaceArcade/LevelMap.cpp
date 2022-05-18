/*
*  Библеотеки
*/

#include "LevelMap.h"
#include "PlayerShipPawn.h"

/*
*  Код
*/

// Иницилизация объекта
ALevelMap::ALevelMap()
{
	PrimaryActorTick.bCanEverTick = true;

	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = MapMesh;

	Partical = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Wave Effect"));
	Partical->SetupAttachment(MapMesh);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(MapMesh);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ALevelMap::OnMeshOverlapBegin);

	ArrowSpawnMapOne = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point One"));
	ArrowSpawnMapOne->SetupAttachment(MapMesh);
}

// Начало действий при создании объекта
void ALevelMap::BeginPlay()
{
	Super::BeginPlay();
	// Жизненый цикл карты
	SetLifeSpan(LifeRange);
}

// Функция пересечения объекта с другими объектами
void ALevelMap::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Проверка на создание
	if (CheckSpawn)
	{
		return;
	}

	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Провернка на игрока
	if (playerShip != OtherActor)
	{
		return;
	}
	else
	{
		// Перезаписть значение
		CheckSpawn = true;

		// Спавним карту
		ALevelMap* LevelMap = GetWorld()->SpawnActor<ALevelMap>(LevelMapClass, ArrowSpawnMapOne->GetComponentLocation(), ArrowSpawnMapOne->GetComponentRotation() + FRotator(0, 0, 0));
	}
}

