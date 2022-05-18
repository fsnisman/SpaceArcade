/*
*	Интерфейсный класс Damage Taker для записи
*	получение урона.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

/*
*  Класс
*/

UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

class SPACEARCADE_API IDamageTaker
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Функции

	// Функция получение урона
	virtual bool TDamage(FDamageData DamageData) = 0;
};
