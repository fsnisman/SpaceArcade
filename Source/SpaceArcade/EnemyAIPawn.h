// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ProjectTileEnemy.h"
#include "PlayerShipPawn.h"
#include "DropItems.h"

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

	UPROPERTY(EditAnywhere, Category = "Materials")
		UMaterialInterface* MaterialOne;

	UPROPERTY(EditAnywhere, Category = "Materials")
		UMaterialInterface* MaterialTwo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClassSpecial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* SpecialShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ExlosionEffectDie;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* FireExlosionEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystem* ExlosionEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		USoundBase* AudioEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;

	UPROPERTY()
		AAIEnemyController* EnemyShipController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop")
		TSubclassOf<ADropItems> DropItem;

	//=========================
	// Create Variables for AI Ship
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireFrequency = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int CountFire = 0;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer Fire")
		float fTimerFire = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bTwoProjectTile = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bScatterProjectTile = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		int CountProjectTile = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		int ScatterProjectTile = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bProjectileRotate360 = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tracking from Player")
		bool bTrackingPlayerArrow = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tracking from Player")
		bool bTrackingPlayerShip = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion Damage")
		float ExplosionDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion Damage")
		float ExplosionDamageEnemy = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score")
		float ScoreDeath = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropCoin = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropLevelUP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropSharp = 0;

	FTimerHandle TimerHandle; //Timer

	int Direction = 1;

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
		void FireBoss();

	UFUNCTION()
		void Fire360();

	UFUNCTION()
		void FireSpecial();

	UFUNCTION()
		bool TDamage(FDamageData DamageData);

	UFUNCTION()
		FVector GetArrowForwardVector();

	UFUNCTION()
		void RotateArrowTo(FVector TargetPosition);

	UFUNCTION()
		void TimerFire();

	UFUNCTION()
		void StopMove();

	UFUNCTION()
		void SetPatrollingPoints(const TArray <ATargetPoint*>& NewPatrollingPoints);

	UFUNCTION()
		TArray<FVector> GetPatrollingPoints();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShake;

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

	TSubclassOf<ADropItems> dDropItem;

	float FMovementComponent(float ValueAxis);
	float FRotationComponent(float ValueAxis);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float TargetForwardAxisValue = 0.f;
	float TargetRightAxisValue = 0.f;
	float CurrentRightAxisValue = 0.f;
	float CurrentForwardAxisValue = 0.f;
	float CheckNumberProjectile = 0;
	
	float ValueTimerStopMove = 0;
	float fMoveSpeed = 0;
	float FRotationSpeed = 0;
	float FMovementAccurancy = 0;
	float FForwardSmootheness = 0;
	float FRotationSmootheness = 0;
	float FfTimerFire = 0;

	int iCountProjectTile = 0;

	FVector ArrowTarget;

	bool tbSetMaterial = false;
	bool tbRotateArrow = false;
	bool tbStoppedMove = true;
	bool tbRotateShip = false;
	bool tbRotateShipToPlayer = false;
	bool tbBackMoveShip = false;
	bool CheckCollisionEnemy = true;
	bool ReadyFire = true; //Check on Ready Shoot Fire
};
