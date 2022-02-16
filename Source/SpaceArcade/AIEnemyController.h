#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"

class AEnemyAIPawn;

UCLASS()
class SPACEARCADE_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
		AEnemyAIPawn* EnemyShipAIPawn;
		APawn* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<FVector> PatrollingPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy")
		float MovementAccurancy = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accuracy = 10;

		int32 CurrentPatrolPointIndex = INDEX_NONE;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Initalize();
	float GetRotationgValue();

	void Targeting();
	bool IsPlayerSeen();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
};
