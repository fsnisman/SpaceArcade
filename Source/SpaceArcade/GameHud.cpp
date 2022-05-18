/*
*  Библеотеки
*/

#include "GameHud.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

/*
*  Код
*/

// Начало действия при создании объекта
void AGameHud::BeginPlay()
{
	Super::BeginPlay();
	// Проверка на мир
	if (GetWorld())
	{
		// Записть контроллера игрока
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		// Проверка на валидность контроллера
		if (PC)
		{
			// Установить значение ввода
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, nullptr, EMouseLockMode::DoNotLock, false);
			// Показывать курсор
			PC->bShowMouseCursor = true;
		}
	}

}

// Венуть текущий виджет
UUserWidget* AGameHud::GetCurrentWidget()
{
	return CurrentWidget;

}

// Удаление текущего виджета из вьюпорта
void AGameHud::RemoveCurrentWidgetFromViewport()
{
	// Проверка на валидность виджета
	if (CurrentWidget)
	{
		// Уничтожить виджет
		CurrentWidget->RemoveFromParent();
		// Записать нулевой виджет
		CurrentWidget = nullptr;
		// Подставить нулевой виджет
		CurrentWidgetID = EWidgetID::None;
	}

}

// Добавление виджета на вьюпорта
UUserWidget* AGameHud::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder)
{
	// Созать текущий виджет
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	
	// Проверка на валидность виджета
	if (CurrentWidget)
	{
		// Добавить виджет на вьюпорт
		CurrentWidget->AddToViewport(ZOrder);
	}

	return CurrentWidget;
}

// Использовать виджет
UUserWidget* AGameHud::UseWidget(EWidgetID widgetID, bool RemovePrevious, int32 ZOrder)
{
	// Проверка на текущий  виджет
	if (CurrentWidgetID == widgetID)
	{
		return CurrentWidget;
	}

	// Уничтожить виджет если не тот вызван
	if (RemovePrevious)
	{
		RemoveCurrentWidgetFromViewport();
	}

	// Массив использованных виджетов
	TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClases.FindRef(widgetID);
	
	// Использовать виджет
	if (WidgetClassToUse.Get())
	{
		// Записать значение id виджета
		CurrentWidgetID = widgetID;
		// Добавить на виьюпорт
		return AddWidgetToViewportByClass(WidgetClassToUse, ZOrder);
	}

	return nullptr;
}