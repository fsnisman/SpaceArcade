#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

UINTERFACE(MinimalAPI)
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

class SPACEARCADE_API IDamageTaker
{
	GENERATED_BODY()

public:
	//virtual bool TDamage(FDamageData DamageData) = 0;
};
