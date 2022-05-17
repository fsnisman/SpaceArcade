#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BalancePlayerState.generated.h"

UCLASS()
class SPACEARCADE_API ABalancePlayerState : public APlayerState
{
	GENERATED_BODY()
	

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int EnemyCount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int iScore = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int Coin = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int Sharp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int PlayerHP = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int LevelShip = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		float ScoreCount = 0;
};
