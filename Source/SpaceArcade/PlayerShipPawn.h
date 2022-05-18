/*
*	Класс Player Ship Pawn для снаряда игрока.
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ProjectTile.h"
#include "BalancePlayerState.h"

#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>


#include "PlayerShipPawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UHealthComponent;
class UCameraComponent;
class UBoxComponent;
class UMatineeCameraShake;


UCLASS()
class SPACEARCADE_API APlayerShipPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:

	//=========================
	// Create Component for Ship
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointOne;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointTwo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointSpecial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTile> ProjectileClassSpecial;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectOne;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectTwo;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffectSpecial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		EProjectType Type = EProjectType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		USoundBase* AudioEffectDie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystem* ExlosionEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffectPunch;

	//=========================
	// Create Variables for Ship
	//=========================

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float SecondTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FrequencyTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireTimer = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeedX = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeedY = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Ship")
		int LevelShip = 1;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool DiedShip = false;

	FTimerHandle TimerHandle; //Timer

public:

	APlayerShipPawn();

	UFUNCTION()
		bool TDamage(FDamageData DamageData);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Count Died Enemy")
		float CountDiedEnemyPawn = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelComplited")
		bool LevelComplitet = false;

	UFUNCTION()
		float GetCurretHealth();

	UFUNCTION()
		float GetMaxHealth();

	UFUNCTION()
		void FireSpecial();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

	UFUNCTION()
		void Fire();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShake;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShakeStart;

public:	

	UFUNCTION()
		void OnRedyOfFire();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool ReadyFire = true; //Check on Ready Shoot Fire
	bool TriggerVingget = false;
	bool SpawnTextFightBoss = false;
};
