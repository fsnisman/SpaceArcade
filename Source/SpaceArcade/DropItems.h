#pragma once

#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "BalancePlayerState.h"
#include "PlayerShipPawn.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItems.generated.h"

UCLASS()
class SPACEARCADE_API ADropItems : public AActor
{
	GENERATED_BODY()

protected:
	
	//=========================
	// Create Component for Drop
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LightEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USoundBase* AudioEffect;

public:	
	ADropItems();

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision 

	//=========================
	// Create Variables for Drop
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountCoin = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountLevelUP = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop Count")
		float DropCountSharp = 1;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
