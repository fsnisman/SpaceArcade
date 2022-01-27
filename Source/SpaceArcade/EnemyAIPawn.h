// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ProjectTile.h"

#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "EnemyAIPawn.generated.h"

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
		UArrowComponent* ProjectileSpawnPointOne;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectOne;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectTwo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		EProjectType Type = EProjectType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true)) // AI Patrolling Points
		TArray<FVector> PatrollingPoints;

	//=========================
	// Create Variables for AI Ship
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy") // AI Movement Accurency
		float MovementAccurancy = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float ForwardSmootheness = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmootheness = 0.1f;

	FTimerHandle TimerHandle; //Timer

public:

	AEnemyAIPawn();

	UFUNCTION()
		TArray<FVector> GetPatrollingPoints()
	{
		return PatrollingPoints;
	};

	UFUNCTION()
		float GetMovementAccurancy()
	{
		return MovementAccurancy;
	};

	UFUNCTION()
		bool TDamage(FDamageData DamageData);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

	UFUNCTION()
		void Fire();

public:

	float FMovementComponent();
	float FRotationComponent(float ValueAxis);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TargetForwardAxisValue = 0.f;
	float TargetRightAxisValue = 0.f;
	float CurrentRightAxisValue = 0.f;
	float CurrentForwardAxisValue = 0.f;

	bool ReadyFire = true; //Check on Ready Shoot Fire
};
