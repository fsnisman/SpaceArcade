/*
*  Библеотеки
*/

#include "PuaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

/*
*  Код
*/

// Инициализация виджета
void UPuaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Проигрования анимации
	PlayAnimation(Animation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
	// Остановить игровое время
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	// Получение название текущего уровня
	SNameLevel = UGameplayStatics::GetCurrentLevelName(this, bRemovePrefixString);
	// Перезацить название уровня
	NameLevel = FName(*SNameLevel);

	// Динамическая инициализация функции "Функция для нажитии кнопки воспроизведния игры"
	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonPlayGameClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки рестарта"
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonRestartGameClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки выхода"
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonExitGameClicked);
	}
}

// Функция для нажитии кнопки рестарта
void UPuaseWidget::OnButtonRestartGameClicked()
{
	// Открыть текущий уровнь
	UGameplayStatics::OpenLevel(this, NameLevel);
	// Удалить все виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

// Функция для нажитии кнопки воспроизведния игры
void UPuaseWidget::OnButtonPlayGameClicked()
{
	// Удалить все виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	// Запусть игровое время
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}

// Функция для нажитии кнопки выхода
void UPuaseWidget::OnButtonExitGameClicked()
{
	// Открыть уровнь меню
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	// Удалить виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
