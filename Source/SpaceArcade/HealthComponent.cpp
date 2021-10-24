#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


bool UHealthComponent::TakeDamage(FDamageData DamageData)
{
	float TakedDamageValue = DamageData.DamageValue;
	CurrentHealth -= TakedDamageValue;

	bool bWasDestroyed = false;
	if (CurrentHealth <= 0)
	{
		bWasDestroyed = true;
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		if (OnDamaged.IsBound())
			OnDamaged.Broadcast(TakedDamageValue);
	}
	return bWasDestroyed;
}


float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}


