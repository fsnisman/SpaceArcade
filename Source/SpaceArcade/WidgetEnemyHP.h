/*
*	Класс Widget Enemy HP для отображение здоровья врагов
*	мировом пространстве.
*/

#pragma once

/*
*  Библеотеки
*/

#include "EnemyAIPawn.h"

#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEnemyHP.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UWidgetEnemyHP : public UUserWidget
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Компоненты

	// Компонент прогресс бара
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* EnemyBarHP;

	//////////////////////////
	//// Функции

	// Инициализация виджета
	virtual void NativeConstruct() override;

	// Обновление виджета каждый игровой тик
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//////////////////////////
	//// Переменные

	// Массив врагов
	TWeakObjectPtr<AEnemyAIPawn> OwnerEnemy;

public:

	//////////////////////////
	//// Функции

	// Установка здоровья врагам
	void SetHealt(float CurretHealth, float MaxHealth);

	// Обновление здоровья
	bool UpdateHealth(float CurretHealth, float MaxHealth);

	// Установка виджета на врага
	void SetOwner(AEnemyAIPawn* InEnemy){ OwnerEnemy = InEnemy; }
};
