/*
*	Библеотеки
*/

#include "GameOverWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

/*
*  Код
*/

// Иницилизация виджета
void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Запуск анимации
	PlayAnimation(Animation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
	// Замедлить игровое время
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);

	// Получение название текущего уровня
	SNameLevel = UGameplayStatics::GetCurrentLevelName(this, bRemovePrefixString);
	// Перезацить название уровня
	NameLevel = FName(*SNameLevel);

	// Динамическая инициализация функции "Нажитии кнопки рестарта"
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonRestartGameClicked);
	}

	// Динамическая инициализация функции "Нажитии кнопки выхода"
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonExitGameClicked);
	}
}

// Нажатие на кнопку рестарт
void UGameOverWidget::OnButtonRestartGameClicked()
{
	// Воспроизвети игровое время
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	// Открытие уровня по названию
	UGameplayStatics::OpenLevel(this, NameLevel);
	// Удалить все виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

// Нажатие на кнопку выход
void UGameOverWidget::OnButtonExitGameClicked()
{
	// Воспроизвети игрове вермя
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	// Войти в игровое меню
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	// Удалить все виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
