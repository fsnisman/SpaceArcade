/*
*	Класс Health Component для здоровья пешки.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "HealthComponent.generated.h"

/*
*  Класс
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEARCADE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//////////////////////////
	//// Делегаты

	// Динамически делегат для получение урона
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, DamageValue);
	// Динамический делегат для значение смерти
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

public:

	//////////////////////////
	//// Переменные

	// Максимальное значение здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
		float MaxHealth = 3;

	// Текущие значение здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
		float CurrentHealth;

	// Значение смерти
	UPROPERTY(BlueprintAssignable)
		FOnDie OnDie;

	// Значение урона
	UPROPERTY(BlueprintAssignable)
		FOnHealthChanged OnDamaged;

public:

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	UHealthComponent();

	// Получение урона
	bool TDamage(FDamageData DamageData);

	// Начало действий при создании объекта
	virtual void BeginPlay() override;

	// Получение текущего значения здоровья
	float GetHealth() const;

	// Получение максимального значения здоровья
	float GetHealthMax() const;

	// Измненеие значение здоровья
	float GetHealthState() const;

	// Добавление значения здоровья
	void AddHealth(float AddiditionalHealthValue);
};
