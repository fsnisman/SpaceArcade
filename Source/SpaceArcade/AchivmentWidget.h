/*
*	Класс Achivment Widget для отображение достижений игрока.
*/

#pragma once

/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"
#include "PlayerGameInstance.h"
#include "GameHud.h"

#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AchivmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPACEARCADE_API UAchivmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Компоненты

	// Комопнент канвас
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	// Компонент грид панель
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UGridPanel* GridPanelButton;

	// Комопонент кнопки меню
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* MenuButton;

	// Компонент кнопки улучшения
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* UpgradeButton;

	// Компонент кнопки достижений
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* AchivmentButton;

	// Компонент кнопки забрать награду за очки
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* GetPrizeScoreButton;

	// Компонент кнопки забрать награду за достижение
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* GetPrizeEnemyButton;

	// Компонент прогресса бара выполнение за заработанные очки
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* PrizeScorePB;

	// Компонент прогресса бара выполенине за уничтожение врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* PrizeEnemyPB;

	// Компонент текст монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	// Компонент текст шарпы
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ShareTextCount;

	// Компонент текст заработанных очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EarnedScoreTextCount;

	// Компонент текст уничтоженных врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EarnedEnemyTextCount;

	// Компонент текст максимальных заработанных очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EarnedScoreTextCountMax;

	// Компонент текст максимальных уничтоженных врагов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EarnedEnemyTextCountMax;

	// Компонент изображения монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	// Компонент изображения шарпов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageShare;

	// Компонент изображения шарпов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* BackgroundAchivement;

protected:

	//////////////////////////
	//// Функции

	// Функция для нажитии кнопки перехода на меню
	UFUNCTION()
		void OnButtonMenuClicked();

	// Функция для нажитии кнопки перехода на улучшение
	UFUNCTION()
		void OnButtonUpgradeClicked();

	// Функция для нажитии кнопки получение приза за полученные очки
	UFUNCTION()
		void OnGetPrizeScoreButtonClicked();

	// Функция для нажитии кнопки получение приза за уничтоженных врагов
	UFUNCTION()
		void OnGetPrizeEnemyButtonClicked();

	// Иницилизация виджета
	virtual void NativeConstruct() override;

	// Обновление виджета в каждом тике
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//////////////////////////
	//// Переменные

	int Prize = 1000;
};
