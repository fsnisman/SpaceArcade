/*
*	Класс Drop Items. При уничтожения врага
*	создается дроп(вещи), которые можно подобрать.
*	Вещи - монеты, шарды, улучшение корабля.
*/

#pragma once

/*
*  Библеотеки
*/

#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "BalancePlayerState.h"
#include "PlayerShipPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItems.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API ADropItems : public AActor
{
	GENERATED_BODY()

protected:
	
	//////////////////////////
	//// Компоненты

	// Компонент тела дропа
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	// Компонент колайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	// Компонент партикла
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LightEffect;

	// Компонент звука
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundBase* AudioEffect;

public:	

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	ADropItems();

	// Функция пересечения с другими объектами
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision 

	//////////////////////////
	//// Переменные

	// Значение количество дропа монет
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountCoin = 1;

	// Значение количество дропа улучшения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountLevelUP = 1;

	// Значение количество дропа шардом
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountSharp = 1;
};
