#pragma once

#include <Components/StaticMeshComponent.h>
#include "Particles/ParticleSystemComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMap.generated.h"

UCLASS()
class SPACEARCADE_API ALevelMap : public AActor
{
	GENERATED_BODY()
	
protected:
	//=========================
	// Create Component for Map
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* MapMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* Partical;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ArrowSpawnMapOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Life Map Time")
		float LifeRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level map params")
		TSubclassOf<ALevelMap> LevelMapClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Movement")
		FVector SpeedMovement;

public:	
	ALevelMap();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Trigger Spawn

	bool CheckSpawn = false;
};
