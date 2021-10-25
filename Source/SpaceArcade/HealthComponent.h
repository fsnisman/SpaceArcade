#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, DamageValue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
		float MaxHealth = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
		float CurrentHealth;

	UPROPERTY(BlueprintAssignable)
		FOnDie OnDie;

	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnDamaged;

public:	
	UHealthComponent();

	bool TakeDamage(FDamageData DamageData);

	virtual void BeginPlay() override;

	float GetHealth() const;

	float GetHealthState() const;
};
