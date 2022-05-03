
#pragma once

#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTileEnemy.generated.h"

UCLASS()
class SPACEARCADE_API AProjectTileEnemy : public AActor
{
	GENERATED_BODY()
	
protected:

	//=========================
	// Create Component for ProjectTile
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* BulletEffect;

	//=========================
	// Create Variables for ProjectTile
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float FlyRange = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;

	FTimerHandle MovementTimerHandle; // Timer

public:	

	AProjectTileEnemy();

	void Start();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision ProjectTile

	UFUNCTION()
		void Move();
};