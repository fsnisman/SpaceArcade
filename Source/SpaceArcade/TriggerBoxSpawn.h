/*
*	Класс Trigger Box Spawn нужен для триггер спавна врагов,
*	когда они ее пересекают.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxSpawn.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API ATriggerBoxSpawn : public ATriggerBox
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Функции

	// Инициализация объекта
	ATriggerBoxSpawn();

	// Функция пересечения
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
