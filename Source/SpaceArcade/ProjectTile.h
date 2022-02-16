// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/UnrealMathUtility.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectTile.generated.h"

UCLASS()
class SPACEARCADE_API AProjectTile : public AActor
{
	GENERATED_BODY()

protected:

	//=========================
	// Create Component for ProjectTile
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LazerEffect;

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

	AProjectTile();

	void Start();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision ProjectTile

	UFUNCTION()
		void Move();

};
