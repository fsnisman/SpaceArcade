/*
*	Класс Project Tile для снаряда игрока.
*/

#pragma once

/*
*  Библеотеки
*/

#include "Math/UnrealMathUtility.h"

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTile.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API AProjectTile : public AActor
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Компоненты

	// Компонент коллайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	// Компонент партикла снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LazerEffect;

	// Компонент звука удара
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects Punch")
		USoundBase* AudioEffectPunch;

	// Компонент партикла удара
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Punch Partical")
		UParticleSystem* CollisionEffect;

	//////////////////////////
	//// Переменные

	// Пременная скорости движения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100;

	// Переменная частота движения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;

	// Переменная дистанция полета
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float FlyRange = 10000.f;

	// Пременная урона
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;

	// Пременная таймера
	FTimerHandle MovementTimerHandle; // Timer

public:	

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	AProjectTile();

	// Функция Начала движения
	void Start();

protected:

	//////////////////////////
	//// Функции

	// Функция пересечения объекта с другими объектами
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision ProjectTile

	// Функция движения 
	UFUNCTION()
		void Move();

};
