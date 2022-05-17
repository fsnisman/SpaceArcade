#include "HealthComponent.h"

// Function for assing a value Health Point
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

// Function Take Damege for Health Component 
bool UHealthComponent::TDamage(FDamageData DamageData)
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

// Function for get Health Point
float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetHealthMax() const
{
	return MaxHealth;
}

// Function for check Health Point
float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}

// Function for Add Health Point
void UHealthComponent::AddHealth(float AddiditionalHealthValue)
{
	CurrentHealth += AddiditionalHealthValue;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}
