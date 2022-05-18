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

	// Переменные улучшения
	float UpgradeDamage = 0;
	float UpgradeHealht = 0;
	float UpgradeReloadSpecialCannon = 0;

	// Переменные уровня улучшения
	int LevelUpgradeDamage = 0;
	int LevelUpgradeHealht = 0;
	int LevelUpgradeReloadSpecialCannon = 0;

	// Констатные перменные максимального уровня улучшения
	const int LevelUpgradeDamageMax = 20;
	const int LevelUpgradeHealhtMax = 20;
	const int LevelUpgradeReloadSpecialCannonMax = 20;

	// Переменные для достижений
	int ChallengeScoreMax = 3000;
	int ChallengeEnemyDiedMax = 100;
};
