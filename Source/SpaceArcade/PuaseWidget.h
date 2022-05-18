/*
*	Класс Puase Widget для отображение паузы.
*/

#pragma once

/*
*  Библеотеки
*/

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuaseWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UPuaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Компоненты

	// Компонент Канвас
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	// Компонент для блюра заднего фона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UBackgroundBlur* BackgroundUI;

	// Компонент для заднего фона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* BackgroundPause;

	// Компонент для кнопки воспроизведения игры
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PlayButton;

	// Комопнент для кнопки рестарта
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* RestartButton;

	// Компонент для кнопки выхода
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* ExitButton;

	// Компонент для анимации
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Animation;

public:
	
	//////////////////////////
	//// Функции

	// Инициализация виджета
	virtual void NativeConstruct() override;

	// Функция для нажитии кнопки рестарта
	UFUNCTION()
		void OnButtonRestartGameClicked();
	
	// Функция для нажитии кнопки воспроизведния игры
	UFUNCTION()
		void OnButtonPlayGameClicked();

	// Функция для нажитии кнопки выхода
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
