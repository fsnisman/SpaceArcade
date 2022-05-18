/*
*  Библеотеки
*/

#include "WidgetEnemyHP.h"

/*
*  Код
*/

// Инициализация виджета
void UWidgetEnemyHP::NativeConstruct()
{
	Super::NativeConstruct();

	// Проверка на создание врага
	if (!OwnerEnemy.IsValid())
	{
		return;
	}

	// Установка значений здоровья врагу
	SetHealt(OwnerEnemy->GetCurretHealth(), OwnerEnemy->GetMaxHealth());
}

// Обновление виджета каждый игровой тик
void UWidgetEnemyHP::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Проверка на создание врага
	if (!OwnerEnemy.IsValid())
	{
		return;
	}

	// Обновление значений здоровья врагу
	UpdateHealth(OwnerEnemy->GetCurretHealth(), OwnerEnemy->GetMaxHealth());
}

// Установка здоровья
void UWidgetEnemyHP::SetHealt(float CurretHealth, float MaxHealth)
{
	// Скрывать виджет, когда здровье полное
	ESlateVisibility WVisibility = ESlateVisibility::Hidden; 

	// Установить текущие значение здровья на максимальное значение здоровья
	CurretHealth = MaxHealth;	

	// Установить значение текущего здоровья и значение видимости виджета
	EnemyBarHP->SetPercent(CurretHealth);					  
	EnemyBarHP->SetVisibility(WVisibility);
}

// Обновление здоровья
bool UWidgetEnemyHP::UpdateHealth(float CurretHealth, float MaxHealth)
{
	// Если изменилось значение текущего здоровья от максимального, то сделать виджет видимым
	if (OwnerEnemy->GetCurretHealth() != OwnerEnemy->GetMaxHealth())
	{
		ESlateVisibility WVisibility = ESlateVisibility::Visible;
		EnemyBarHP->SetVisibility(WVisibility);
	}

	// Обновление виджет по текущему здоровью
	bool bWasDestroyed = false;
	float Percent = CurretHealth / MaxHealth;
	EnemyBarHP->SetPercent(Percent);

	// Проверка текущего значения здоровья на нуль, если да, то скрыть виджет
	if (OwnerEnemy->GetCurretHealth() <= 0)
	{
		ESlateVisibility WVisibility = ESlateVisibility::Hidden;
		EnemyBarHP->SetVisibility(WVisibility);
	}

	return false;
}