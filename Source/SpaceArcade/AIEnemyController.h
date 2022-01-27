#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"

class AEnemyAIPawn;
class APlayerShipPawn;

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

		int32 CurrentPatrolPointIndex = INDEX_NONE;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Initalize();
	float GetRotationgValue();
};
