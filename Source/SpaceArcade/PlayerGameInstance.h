/*
*	Класс Player Game Instance для глобыльной иформации игрового цикла
*	Хранит в себе переменные баланса, улучшений, достижений.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerGameInstance.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Переменный игрока

	// Переменный баланса игрока
	int ScoreOfPlayre = 0;
	int CoinOfPlayer = 0;
	int ShardOfPlayer = 0;
	int EnemyDiedCountOfPlayer = 0;

	// Переменные улучшения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float UpgradeDamage = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float UpgradeHealht = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float UpgradeReloadSpecialCannon = 1;


	// Переменные максимлаьного уровня улучшения
	int LevelUpgradeDamage = 1;
	int LevelUpgradeHealht = 1;
	int LevelUpgradeReloadSpecialCannon = 1;

	// Констатные перменные максимального уровня улучшения
	const int LevelUpgradeDamageMax = 20;
	const int LevelUpgradeHealhtMax = 20;
	const int LevelUpgradeReloadSpecialCannonMax = 20;

	// Переменные для максимального количества достижений
	int ChallengeScoreMax = 3000;
	int ChallengeEnemyDiedMax = 100;
};
