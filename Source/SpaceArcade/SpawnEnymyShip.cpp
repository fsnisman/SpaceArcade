#include "SpawnEnymyShip.h"
#include "TimerManager.h"
#include "TriggerBoxSpawn.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

ASpawnEnymyShip::ASpawnEnymyShip()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	EnemySpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Setup arrow direction"));
	EnemySpawnPoint->AttachToComponent(sceneComp, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(sceneComp);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpawnEnymyShip::OnMeshOverlapBegin);

}

void ASpawnEnymyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this)
	{
		AddActorWorldOffset(FVector(SpeedMovement + DeltaTime));
	}
}

void ASpawnEnymyShip::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FTimerHandle TargetingTimerHandle;

	for (TActorIterator<ATriggerBoxSpawn> TriggerItr(GetWorld()); TriggerItr; ++TriggerItr)
	{
		ATriggerBoxSpawn* TriggerActor = *TriggerItr;

		if (OtherActor == TriggerActor)
		{
			SpeedMovement = FVector(0, 0, 0);
			TimerSpawn();
			break;
		}
		else
		{
			break;
		}
	}
}

void ASpawnEnymyShip::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnEnymyShip::SpawnEnemyShip()
{
	FTimerHandle TargetingTimerHandle;

	if (NumberCount < CountEnemy)
	{
		FTransform SpawnTransform(EnemySpawnPoint->GetComponentRotation(), EnemySpawnPoint->GetComponentLocation(), FVector(1));
		
		NumberCount++;

		AEnemyAIPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyAIPawn>(SpawnEnemyClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		NewEnemy->tbRotateShip = bRotateShipTrigger;
		NewEnemy->tbBackMoveShip = bBackMoveShipTrigger;

		NewEnemy->SetPatrollingPoints(EnemyTrackingPoints);

		UGameplayStatics::FinishSpawningActor(NewEnemy, SpawnTransform);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(TargetingTimerHandle);
	}
}

void ASpawnEnymyShip::TimerSpawn()
{
	FTimerHandle TargetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnEnymyShip::SpawnEnemyShip, SpawnEnemyRate, true, SpawnEnemyRate);
}

