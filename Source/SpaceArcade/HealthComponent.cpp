/*
*  Библеотеки
*/

#include "HealthComponent.h"

/*
*  Код
*/

// Инцилизация объекта
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
}

// Начало действий при создании объекта
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// Приписывание значения максимального здоровья к текущему
	CurrentHealth = MaxHealth;
}

// Получение урона 
bool UHealthComponent::TDamage(FDamageData DamageData)
{
	// Значение урона
	float TakedDamageValue = DamageData.DamageValue;
	// Вычитание текущего значение от урона
	CurrentHealth -= TakedDamageValue;

	bool bWasDestroyed = false;
	// Проверка на значение текущего значения
	if (CurrentHealth <= 0)
	{
		// Уничтожения объекта
		bWasDestroyed = true;
		if (OnDie.IsBound())
			OnDie.Broadcast();
	}
	else
	{
		// Измеенеия здоровья объекту
		if (OnDamaged.IsBound())
			OnDamaged.Broadcast(TakedDamageValue);
	}
	return bWasDestroyed;
}

// Получение текущего здоровья
float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

// Получение максимального здоровья
float UHealthComponent::GetHealthMax() const
{
	return MaxHealth;
}

// Обновление значения здоровья
float UHealthComponent::GetHealthState() const
{
	return CurrentHealth / MaxHealth;
}

// Добавление здоровья к текущему здоровью
void UHealthComponent::AddHealth(float AddiditionalHealthValue)
{
	CurrentHealth += AddiditionalHealthValue;
	if (CurrentHealth > MaxHealth)
		CurrentHealth = MaxHealth;
}
