/*
*	Класс Game Structs для игровой структуры игры.
*   Хранит в себе значение урона, инстигаторы, типы снарядов.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

/*
*  Класс
*/

USTRUCT()
struct FDamageData
{
    GENERATED_BODY()

     /////////////////////////
    //// Переменные

    // Значение урона
    UPROPERTY()
        float DamageValue;
    
    // Инстигатор
    UPROPERTY()
        AActor* Instigator;
    
    // Пометка от кого урон
    UPROPERTY()
        AActor* DamageMaker;
};

/*
*  Перечисление
*/

// Перечисление типа снарядов
UENUM(BlueprintType)
enum class EProjectType : uint8 {
    FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
    FireSpecial = 1  UMETA(DisplayName = "Use special projectile")
};
