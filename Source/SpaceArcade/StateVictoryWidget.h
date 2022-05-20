/*
*	Класс State Victory Widget для отображение статистики победы,
*	где выводятся данный заработанный очков, монет и уничтоженных врагов.
*/

#pragma once

/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"
#include "PlayerGameInstance.h"

#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StateVictoryWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UStateVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	//////////////////////////
	//// Компоненты

	// Компонент Канвас
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	// Комопнент кнопки в возращение в меню
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* MenuBackButton;

	// Компонент отображение текста монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinText;

	// Компонент отображение текста врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyText;

	// Компонент отображение текста очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreCount;

	// Компонент текста для значение заработанных монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	// Компонент текста для значение уничтоженых врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyTextCount;

	// Компонент текста для значение заработанных очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	// Компонент изображение монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	// Компонент изображение врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageEnemy;

	// Компонент изображение заднего фона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageBackground;

protected:

	//////////////////////////
	//// Функции

	// Инициализации виджета
	virtual void NativeConstruct() override;

public:

	//////////////////////////
	//// Функции

	// Нажатие на кнопку возращение в меню
	UFUNCTION()
		void OnButtonMenuBackClicked();

	//////////////////////////
	//// Переменные

	// Значение очков
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Score = 0;

	// Значение монет
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Coin = 0;

	// Значение врагов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Enemy = 0;
};
