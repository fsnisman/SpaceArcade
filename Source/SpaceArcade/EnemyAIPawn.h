// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ProjectTileEnemy.h"
#include "PlayerShipPawn.h"

#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"


#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "EnemyAIPawn.generated.h"

class AAIEnemyController;
class UStaticMeshComponent;
class USpringArmComponent;
class UHealthComponent;
class UCameraComponent;
class UBoxComponent;


UCLASS()
class SPACEARCADE_API AEnemyAIPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:
	//=========================
	// Create Component for Ship
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystem* ExlosionEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY()
		AAIEnemyController* EnemyShipController;

	//=========================
	// Create Variables for AI Ship
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireFrequency = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		bool bFireToPlayer = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy") // AI Movement Accurency
		float MovementAccurancy = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float ForwardSmootheness = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmootheness = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Count ProjectTile")
		int CountProjectTile = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scatter ProjectTile")
		int ScatterProjectTile = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tracking from Player")
		bool bTrackingPlayer = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion Damage")
		float ExplosionDamage = 1;

	FTimerHandle TimerHandle; //Timer

public:

	AEnemyAIPawn();

	UFUNCTION()
		float GetMovementAccurancy()
	{
		return MovementAccurancy;
	};

	UFUNCTION()
		void Fire();

	UFUNCTION()
		bool TDamage(FDamageData DamageData);

	UFUNCTION()
		FVector GetArrowForwardVector();

	UFUNCTION()
		void RotateArrowTo(FVector TargetPosition);

	UFUNCTION()
		void TimerFire();

	UFUNCTION()
		void SetPatrollingPoints(const TArray <ATargetPoint*>& NewPatrollingPoints);

	UFUNCTION()
		TArray<FVector> GetPatrollingPoints();

	void EnableCollision();
	FVector GetEyesPosition();


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision 

public:

	float FMovementComponent(float ValueAxis);
	float FRotationComponent(float ValueAxis);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TargetForwardAxisValue = 0.f;
	float TargetRightAxisValue = 0.f;
	float CurrentRightAxisValue = 0.f;
	float CurrentForwardAxisValue = 0.f;
	float CheckNumberProjectile = 0;
	FVector ArrowTarget;

	bool CheckCollisionEnemy = true;
	bool ReadyFire = true; //Check on Ready Shoot Fire
};
