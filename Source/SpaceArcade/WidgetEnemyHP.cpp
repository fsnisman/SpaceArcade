#include "WidgetEnemyHP.h"

void UWidgetEnemyHP::NativeConstruct()
{
	Super::NativeConstruct();

	if (!OwnerEnemy.IsValid())
	{
		return;
	}

	SetHealt(OwnerEnemy->GetCurretHealth(), OwnerEnemy->GetMaxHealth());
}


void UWidgetEnemyHP::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerEnemy.IsValid())
	{
		return;
	}

	UpdateHealth(OwnerEnemy->GetCurretHealth(), OwnerEnemy->GetMaxHealth());
}

void UWidgetEnemyHP::SetHealt(float CurretHealth, float MaxHealth)
{
	ESlateVisibility WVisibility = ESlateVisibility::Hidden;

	CurretHealth = MaxHealth;
	EnemyBarHP->SetPercent(CurretHealth);
	EnemyBarHP->SetVisibility(WVisibility);
}

bool UWidgetEnemyHP::UpdateHealth(float CurretHealth, float MaxHealth)
{
	if (OwnerEnemy->GetCurretHealth() != OwnerEnemy->GetMaxHealth())
	{
		ESlateVisibility WVisibility = ESlateVisibility::Visible;
		EnemyBarHP->SetVisibility(WVisibility);
	}

	bool bWasDestroyed = false;
	float Percent = CurretHealth / MaxHealth;
	EnemyBarHP->SetPercent(Percent);

	if (OwnerEnemy->GetCurretHealth() <= 0)
	{
		ESlateVisibility WVisibility = ESlateVisibility::Hidden;
		EnemyBarHP->SetVisibility(WVisibility);
	}

	return false;
}