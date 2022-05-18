/*
*	Класс Game Over Widget. Показывает экраг проигрыша.
*/

#pragma once

/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//////////////////////////
	//// Компоненты

	// Компонент канвас
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	// Компонент кнопки рестарт
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* RestartButton;

	// Комонент кнопки выхода
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* ExitButton;

	// Компонент текста "Игра оконченка"
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* GameOver;

	// Компонент изображение фона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* BackgroundUI;

	// Компонент размытия заднего фона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UBackgroundBlur* BackgroundBlurUI;

	// Компонент анимации
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Animation;

public:

	//////////////////////////
	//// Функции

	// Иницилизация виджета
	virtual void NativeConstruct() override;

	// Нажатие на кнопку рестарт
	UFUNCTION()
		void OnButtonRestartGameClicked();

	// Нажатие на кнопку выхода
	UFUNCTION()
		void OnButtonExitGameClicked();

public:

	//////////////////////////
	//// Переменные

	// Переменная названия уровня
	FName NameLevel;

	// Стринговая переменая для названия уровня
	FString SNameLevel;

	bool bRemovePrefixString = true;
};
