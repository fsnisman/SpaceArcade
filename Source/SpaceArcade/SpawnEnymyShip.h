#pragma once

#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

#include "CoreMinimal.h"
#include "EnemyAIPawn.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "SpawnEnymyShip.generated.h"

UCLASS()
class SPACEARCADE_API ASpawnEnymyShip : public AActor
{
	GENERATED_BODY()
	
protected:

	//=========================
	// Create Component for Spawn
	//=========================

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* EnemySpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		TSubclassOf<AEnemyAIPawn> SpawnEnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateShipTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateShipToPlayerTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bRotateArrowTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bBackMoveShipTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bStopMoveTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		bool bMoveRightLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		float fValueTimerStopMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		float SpawnEnemyRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfMoveSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfRotationSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfMovementAccurancy = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfForwardSmootheness = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Movement")
		float tfRotationSmootheness = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Timer")
		float tffTimerFire = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params |  Count ProjectTile")
		int tCountProjectTile = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn enemy params")
		TArray<ATargetPoint*> EnemyTrackingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count Enemy")
		float CountEnemy = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Died Enemy")
		float DiedEnemy = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Boss")
		bool SpawnBoss = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed Movement")
		FVector SpeedMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drop")
		TSubclassOf<ADropItems> tDropItem;

public:	
	
	ASpawnEnymyShip();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Trigger

	float NumberCount = 0;

protected:

	virtual void BeginPlay() override;

	void SpawnEnemyShip();

	void TimerSpawn();
};
