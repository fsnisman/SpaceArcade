/*
*	Класс AI Enemy Controller.
*	Примитивный исскуственный интелект для врага.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"

/*
*  Класс
*/

class AEnemyAIPawn;

UCLASS()
class SPACEARCADE_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()
	
protected:

	//////////////////////////
	//// Переменные

	// Переменные пешки врага и игрока
	UPROPERTY()
		AEnemyAIPawn* EnemyShipAIPawn;
		APawn* PlayerPawn;

	// Массив точек патруля
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;

	// Частота перемещения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy")
		float MovementAccurancy = 0.0f;

	// Реакция на точку патруля
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;

	// Скорость перещения на следующую точку
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;

	// Частота перемещения на следующую точку
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accuracy = 10;

	// Количетсво точек патруля 
	int32 CurrentPatrolPointIndex = INDEX_NONE;

	// Переменная таймера
	FTimerHandle TimerHandle;

protected:

	//////////////////////////
	//// Функции

	// Начало действия при создании объекта
	virtual void BeginPlay() override;

	// Обновление объекта в каждом тике 
	virtual void Tick(float DeltaTime) override;

	// Иницилизация объекта
	void Initalize();

	// Получение значение поворота на следующую точку
	float GetRotationgValue();
};
