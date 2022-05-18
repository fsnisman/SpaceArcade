/*
*	����� Player Game Instance ��� ���������� ��������� �������� �����
*	������ � ���� ���������� �������, ���������, ����������.
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerGameInstance.generated.h"

UCLASS()
class SPACEARCADE_API UPlayerGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//////////////////////////
	//// ���������� ������

	// ���������� ������� ������
	int ScoreOfPlayre = 0;
	int CoinOfPlayer = 0;
	int ShardOfPlayer = 0;

	// ���������� ���������
	float UpgradeDamage = 0;
	float UpgradeHealht = 0;
	float UpgradeReloadSpecialCannon = 0;

	// ���������� ������ ���������
	int LevelUpgradeDamage = 0;
	int LevelUpgradeHealht = 0;
	int LevelUpgradeReloadSpecialCannon = 0;

	// ���������� ��������� ������������� ������ ���������
	const int LevelUpgradeDamageMax = 20;
	const int LevelUpgradeHealhtMax = 20;
	const int LevelUpgradeReloadSpecialCannonMax = 20;

	// ���������� ��� ����������
	int ChallengeScoreMax = 3000;
	int ChallengeEnemyDiedMax = 100;
};
