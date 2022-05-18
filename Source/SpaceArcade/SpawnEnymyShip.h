/*
*	Класс Spawn Enemy Ship для спавна врагов.
*/

#pragma once

/*
*  Библеотеки
*/

#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "CoreMinimal.h"
#include "EnemyAIPawn.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "SpawnEnymyShip.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API ASpawnEnymyShip : public AActor
{
	GENERATED_BODY()
	
protected:

	//////////////////////////
	//// Компоненты

	// Компонент направление
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* EnemySpawnPoint;

	// Компонент коллайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	//////////////////////////
	//// Переменные

	// Массив спаврнов врагов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		TSubclassOf<AEnemyAIPawn> SpawnEnemyClass;
	
	// Проверка на поворот корабля
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateShipTrigger;

	// Проверка поворот корабля на игрока
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateShipToPlayerTrigger;

	// Проверка на поворот направления стрельбы
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateArrowTrigger;

	// Проверка на движение корабля задом
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bBackMoveShipTrigger;

	// Проверка на остановку корабля
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bStopMoveTrigger;

	// Проверка на движение корабля вправо-влево
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bMoveRightLeft;

	// Значение на сколько остановить корабль
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		float fValueTimerStopMove;

	// Значение на частосту спавна врагов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		float SpawnEnemyRate = 1;

	// Значение скорости движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfMoveSpeed = 1;

	// Значение скорости поворота
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfRotationSpeed = 1;

	// Значение точности движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfMovementAccurancy = 1;

	// Значение склаживания движения вперед
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfForwardSmootheness = 1;

	// Значение склаживания движения пововрота
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfRotationSmootheness = 1;

	// Значения таймера, когда коллизия становится активной
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Timer")
		float tffTimerFire = 1;

	// Значения сколько выпустить снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Count ProjectTile")
		int tCountProjectTile = 1;

	// Массив точек для движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		TArray<ATargetPoint*> EnemyTrackingPoints;

	// Значения сколько спавнить врагов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count Enemy")
		float CountEnemy = 5;

	// Значения скольков врагов убито
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Died Enemy")
		float DiedEnemy = 0;

	// Проверка на спавн босса
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Boss")
		bool SpawnBoss = false;

	// Проверка на особенного врага
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Boss")
		bool SpawnSpecialEnemy = false;

	// Вектор скорости движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Movement")
		FVector SpeedMovement;

	// Массив дропа
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
		TSubclassOf<ADropItems> tDropItem;

	// Массив на особенного дропа
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
		TSubclassOf<ADropItems> tDropItemSpecial;

public:	
	
	//////////////////////////
	//// Функции

	// Инициализация объекта
	ASpawnEnymyShip();

	// Обновление объекта в каждом тике
	virtual void Tick(float DeltaTime) override;

	// Функция пересечения объекта с другими объектами
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Trigger

	//////////////////////////
	//// Переменные

	// Значение количество заспавненных врагов
	float NumberCount = 0;

protected:

	//////////////////////////
	//// Функции

	// Создание врагов
	void SpawnEnemyShip();

	// Частоста создание врагов
	void TimerSpawn();
};
