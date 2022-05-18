/*
*	Класс Player Matinee Camera Shake для тряски камеры.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "PlayerMatineeCameraShake.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UPlayerMatineeCameraShake : public UMatineeCameraShake
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	UPlayerMatineeCameraShake();
};
