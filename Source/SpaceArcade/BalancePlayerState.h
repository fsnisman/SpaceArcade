/*
*	Класс Balance Player State для данных игрока
*	в игровой сессии.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BalancePlayerState.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API ABalancePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Переменные

	// Значение уничтоженных врагов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int EnemyCount = 0;

	// Значение заработанных очков
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int iScore = 0;

	// Значение заработанных монет
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int Coin = 0;

	// Значение заработанных шардов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int Sharp = 0;

	// Значение здоровья у игрока
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int PlayerHP = 0;

	// Значение уровнять у игрока
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		int LevelShip = 1;

	// Значение общего количества заработанных очков
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Balance")
		float ScoreCount = 0;
};
