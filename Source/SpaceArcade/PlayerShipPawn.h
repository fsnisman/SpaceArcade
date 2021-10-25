#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

//#include "DamageTaker.h"
#include "HealthComponent.h"

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


UCLASS()
class SPACEARCADE_API APlayerShipPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectTileSetupArrow;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 1.f;

public:

	APlayerShipPawn();

	/*UFUNCTION()
		bool TDamage(FDamageData DamageData) override;*/

protected:
	virtual void BeginPlay() override;

	/*UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);*/

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
