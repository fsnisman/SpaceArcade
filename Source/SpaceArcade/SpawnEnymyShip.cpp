/*
*  Библеотеки
*/

#include "SpawnEnymyShip.h"
#include "TimerManager.h"
#include "GameHud.h"
#include "TriggerBoxSpawn.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

/*
*  Код
*/

// Иницилизация объекта
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

// Обновление объекта в каждом тике
void ASpawnEnymyShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Каст на худ
	AGameHud* GameHud = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	// Проверка на объект и на паузу, если нет, то объект движется
	if (this && GameHud->bPause == false)
	{
		AddActorWorldOffset(FVector(SpeedMovement + DeltaTime));
	}
}

// Функция пересечения объекта с другими объектами
void ASpawnEnymyShip::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Цикл перебора тригер для проверки на пересечения с другими объектами
	for (TActorIterator<ATriggerBoxSpawn> TriggerItr(GetWorld()); TriggerItr; ++TriggerItr)
	{
		ATriggerBoxSpawn* TriggerActor = *TriggerItr;

		// Если пересекает с другим объектом, то остановить и вызвать функцию спавна врагов
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

// Создание врагов
void ASpawnEnymyShip::SpawnEnemyShip()
{
	// Переменна для таймера
	FTimerHandle TargetingTimerHandle;

	// Проверка на наличие тега "SpawnBoss"
	if (this->ActorHasTag((TEXT("SpawnBoss"))))
	{
		// Проверка на SpawnBoss
		if (SpawnBoss == true)
		{
			// Переменная для движения
			FTransform SpawnTransform(EnemySpawnPoint->GetComponentRotation(), EnemySpawnPoint->GetComponentLocation(), FVector(1));
			// Переменная на каст игрока
			APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
			// Переменная спавн врага
			AEnemyAIPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyAIPawn>(SpawnEnemyClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			// Вызов текста с сражением босса
			playerShip->SpawnTextFightBoss = true;

			// Перезапись значение врага из этого класса
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

			// Установка по каким точкам двигаться
			NewEnemy->SetPatrollingPoints(EnemyTrackingPoints);

			// Когда остановить спавн
			UGameplayStatics::FinishSpawningActor(NewEnemy, SpawnTransform);

			//Перезапись перменной
			SpawnBoss = false;
		}
	}
	else
	{
		// Проверка на количество врагов
		if (NumberCount < CountEnemy)
		{
			// Переменная для движения
			FTransform SpawnTransform(EnemySpawnPoint->GetComponentRotation(), EnemySpawnPoint->GetComponentLocation(), FVector(1));

			NumberCount++;

			// Переменная спавн врага
			AEnemyAIPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyAIPawn>(SpawnEnemyClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			// Перезапись значение врага из этого класса
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

			// Проверка на создание специального врага
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

			// Установка по каким точкам двигаться
			NewEnemy->SetPatrollingPoints(EnemyTrackingPoints);

			// Когда остановить спавн
			UGameplayStatics::FinishSpawningActor(NewEnemy, SpawnTransform);
		}
		else
		{
			// Уничтожение объекта
			Destroy();

			// Очистка таймера
			GetWorld()->GetTimerManager().ClearTimer(TargetingTimerHandle);
		}
	}
}

// Таймер спавна
void ASpawnEnymyShip::TimerSpawn()
{
	// Переменная для таймера
	FTimerHandle TargetingTimerHandle;

	// Запуск таймера для спавна врагов
	GetWorld()->GetTimerManager().SetTimer(TargetingTimerHandle, this, &ASpawnEnymyShip::SpawnEnemyShip, SpawnEnemyRate, true, SpawnEnemyRate);
}

