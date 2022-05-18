/*
*	Класс Game Hud. Нужен для менеджмента виджетов.
*	Хранит в себе все виджеты и переключает между ними.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHud.generated.h"

/*
*  Перечисление
*/

// Название виджетов
UENUM()
enum class EWidgetID : uint8
{
	None,
	MainMenu,
	PauseMenu,
	GameInteface,
	UpgradeMenu,
	LevelMenu,
	GameOverMenu,
	LoadingWidget,
	VictoryTextWidget,
	StateVictoryWidget,
	AchievementsMenu
};

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API AGameHud : public AHUD
{
	GENERATED_BODY()
	
protected:

	//////////////////////////
	//// Переменные

	// Массив виджетов
	UPROPERTY(EditAnywhere)
		TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClases;

	// Текущий виджет
	UPROPERTY()
		UUserWidget* CurrentWidget;

	// ID Виджета
	EWidgetID CurrentWidgetID;

public:

	//////////////////////////
	//// Функции

	// Начало действия при создании объекта
	void BeginPlay() override;
	
	// Удаление текущего виджета из вьюпорта
	void RemoveCurrentWidgetFromViewport();

	// Использование виджета
	UFUNCTION(BlueprintCallable)
	UUserWidget* UseWidget(EWidgetID widgetID, bool RemovePrevious = true, int32 ZOrder = 0);

	// Получение текущего виджета
	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget();

	// Добавление виджета на вьюпорта
	UFUNCTION(BlueprintCallable)
	UUserWidget* AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);

	//////////////////////////
	//// Переменные

	// Переменная на паузу
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bPause;
};
