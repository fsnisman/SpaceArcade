/*
*	Класс Game Widget для отображение игрового интерфейса.
*/

#pragma once

/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"

#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// Компоненты

	// Комопнент канвас
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	// Компонент кнопки паузы
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PauseButton;

	// Компонент кнопки особого орудия 
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* SpecialCannonButton;

	// Компонент прогресса бара здоровья игрока
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* PlayerPBHP;

	// Компонент заднего фона прогресса бара здоровья игрока 
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* BackgroundPlayerPBHP;

	// Компонент текста отображения значение здоровья
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* PlayerTextPBHP;

	// Компонент текста отображения значение монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	// Компонент текста отображения значение врагов уничтоженных
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyTextCount;

	// Компонент текста отображения значение очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	// Компонент текста босса
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* BossText;

	// Компонент текста сражения
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* FightText;

	// Компонент текста числа один
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberOneText;

	// Компонент текста числа два
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberTwoText;

	// Компонент текста числа три
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberThreeText;

	// Компонент изображение старта
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageStart;
	
	// Компонент изображение монетки
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	// Компонент изображение врага
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageEnemy;

	// Компонент изображение виньетки
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageVignette;

	// Компонент анимация виньетки
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* VignetteAnimation;

	// Компонент анимация босс файта
	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* BossFightAnimation;

protected:

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	virtual void NativeConstruct() override;

	// Обновление объекта в каждом тике
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//////////////////////////
	//// Переменные

	// Массив пешки игрока
	TWeakObjectPtr<APlayerShipPawn> OwnerPlayer;

public:

	//////////////////////////
	//// Функции

	// Нажатие на кнопку паузы
	UFUNCTION()
		void OnButtonPauseGameClicked();

	// Нажатие на кнопку особого орудия
	UFUNCTION()
		void OnButtonSpecialCannonClicked();

	// Установить значение здоровья
	void SetHealt(float CurretHealth, float MaxHealth);

	// Обновление виджета в каждом тике
	bool UpdateWidget(float CurretHealth, float MaxHealth);
};
