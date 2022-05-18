/*
*	Класс Level Map для карты.
*/

#pragma once

/*
*  Библеотеки
*/

#include <Components/StaticMeshComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMap.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API ALevelMap : public AActor
{
	GENERATED_BODY()
	
protected:
	
	//////////////////////////
	//// Компоненты

	// Компонент тела для карты
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MapMesh;

	// Компоненты партикла
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* Partical;

	// Компоненты клайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	// Компонент направление спавная карты
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ArrowSpawnMapOne;

	//////////////////////////
	//// Переменные

	// Переменая жизни карты
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life Map Time")
		float LifeRange = 10000.f;

	// Массив карт
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level map params")
		TSubclassOf<ALevelMap> LevelMapClass;

	// Вектор скорости движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Movement")
		FVector SpeedMovement;

protected:

	//////////////////////////
	//// Функции

	// Начало действий при создании объекта
	virtual void BeginPlay() override;

public:	

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	ALevelMap();

	// Функция пересечения объекта с другими объектами
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Trigger Spawn

	//////////////////////////
	//// Пременные

	// Проверка на спавн
	bool CheckSpawn = false;
};
