/*
*  ����������
*/

#include "SpawnEnymyShip.h"
#include "TimerManager.h"
#include "GameHud.h"
#include "TriggerBoxSpawn.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

/*
*  ���
*/

// ������������ �������
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

// ���������� ������� � ������ ����
void ASpawnEnymyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// ���� �� ���
	AGameHud* GameHud = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// �������� �� ������ � �� �����, ���� ���, �� ������ ��������
	if (this && GameHud->bPause == false)
	{
		AddActorWorldOffset(FVector(SpeedMovement + DeltaTime));
	}
}

// ������� ����������� ������� � ������� ���������
void ASpawnEnymyShip::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���� �������� ������ ��� �������� �� ����������� � ������� ���������
	for (TActorIterator<ATriggerBoxSpawn> TriggerItr(GetWorld()); TriggerItr; ++TriggerItr)
	{
		ATriggerBoxSpawn* TriggerActor = *TriggerItr;

		// ���� ���������� � ������ ��������, �� ���������� � ������� ������� ������ ������
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

// �������� ������
void ASpawnEnymyShip::SpawnEnemyShip()
{
	// ��������� ��� �������
	FTimerHandle TargetingTimerHandle;

	// �������� �� ������� ���� "SpawnBoss"
	if (this->ActorHasTag((TEXT("SpawnBoss"))))
	{
		// �������� �� SpawnBoss
		if (SpawnBoss == true)
		{
			// ���������� ��� ��������
			FTransform SpawnTransform(EnemySpawnPoint->GetComponentRotation(), EnemySpawnPoint->GetComponentLocation(), FVector(1));
			// ���������� �� ���� ������
			APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
			// ���������� ����� �����
			AEnemyAIPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyAIPawn>(SpawnEnemyClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			// ����� ������ � ��������� �����
			playerShip->SpawnTextFightBoss = true;

			// ���������� �������� ����� �� ����� ������
			NewEnemy->tbRotateShip = bRotateShipTrigger;
			NewEnemy->tbBackMoveShip = bBackMoveShipTrigger;
			NewEnemy->tbStoppedMove = bStopMoveTrigger;
			NewEnemy->tbRotateArrow = bRotateArrowTrigger;
			NewEnemy->tbRotateShipToPlayer = bRotateShipToPlayerTrigger;
			NewEnemy->ValueTimerStopMove = fValueTimerStopMove;
			NewEnemy->fMoveSpeed = tfMoveSpeed;
			NewEnemy->FRotationSpeed = tfRotationSpeed;
			NewEnemy->FMovementAccurancy = tfMovementAccurancy;
			NewEnemy->FForwardSmootheness = tfForwardSmootheness;
			NewEnemy->FRotationSmootheness = tfRotationSmootheness;
			NewEnemy->FfTimerFire = tffTimerFire;
			NewEnemy->iCountProjectTile = tCountProjectTile;
			NewEnemy->dDropItem = tDropItem;

			// ��������� �� ����� ������ ���������
			NewEnemy->SetPatrollingPoints(EnemyTrackingPoints);

			// ����� ���������� �����
			UGameplayStatics::FinishSpawningActor(NewEnemy, SpawnTransform);

			//���������� ���������
			SpawnBoss = false;
		}
	}
	else
	{
		// �������� �� ���������� ������
		if (NumberCount < CountEnemy)
		{
			// ���������� ��� ��������
			FTransform SpawnTransform(EnemySpawnPoint->GetComponentRotation(), EnemySpawnPoint->GetComponentLocation(), FVector(1));

			NumberCount++;

			// ���������� ����� �����
			AEnemyAIPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyAIPawn>(SpawnEnemyClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			// ���������� �������� ����� �� ����� ������
			NewEnemy->tbRotateShip = bRotateShipTrigger;
			NewEnemy->tbBackMoveShip = bBackMoveShipTrigger;
			NewEnemy->tbStoppedMove = bStopMoveTrigger;
			NewEnemy->tbRotateArrow = bRotateArrowTrigger;
			NewEnemy->tbRotateShipToPlayer = bRotateShipToPlayerTrigger;
			NewEnemy->ValueTimerStopMove = fValueTimerStopMove;
			NewEnemy->fMoveSpeed = tfMoveSpeed;
			NewEnemy->FRotationSpeed = tfRotationSpeed;
			NewEnemy->FMovementAccurancy = tfMovementAccurancy;
			NewEnemy->FForwardSmootheness = tfForwardSmootheness;
			NewEnemy->FRotationSmootheness = tfRotationSmootheness;
			NewEnemy->FfTimerFire = tffTimerFire;
			NewEnemy->iCountProjectTile = tCountProjectTile;

			// �������� �� �������� ������������ �����
			if (SpawnSpecialEnemy && NumberCount == CountEnemy)
			{
				tDropItem = tDropItemSpecial;
				NewEnemy->dDropItem = tDropItem;
				NewEnemy->tbSetMaterial = true;
			}
			else
			{
				NewEnemy->dDropItem = tDropItem;
			}

			// ��������� �� ����� ������ ���������
			NewEnemy->SetPatrollingPoints(EnemyTrackingPoints);

			// ����� ���������� �����
			UGameplayStatics::FinishSpawningActor(NewEnemy, SpawnTransform);
		}
		else
		{
			// ����������� �������
			Destroy();

			// ������� �������
			GetWorld()->GetTimerManager().ClearTimer(TargetingTimerHandle);
		}
	}
}

// ������ ������
void ASpawnEnymyShip::TimerSpawn()
{
	// ���������� ��� �������
	FTimerHandle TargetingTimerHandle;

	// ������ ������� ��� ������ ������
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnEnymyShip::SpawnEnemyShip, SpawnEnemyRate, true, SpawnEnemyRate);
}

