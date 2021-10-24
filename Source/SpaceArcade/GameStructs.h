#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

USTRUCT()
struct FDamageData
{
    GENERATED_BODY()

        UPROPERTY()
        float DamageValue;
    UPROPERTY()
        AActor* Instigator;
    UPROPERTY()
        AActor* DamageMaker;
};