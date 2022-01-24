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

UENUM(BlueprintType)
enum class EProjectType : uint8 {
    FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
    FireSpecial = 1  UMETA(DisplayName = "Use special projectile")
};
