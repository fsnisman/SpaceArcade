/*
*	Класс Menu Widget для отображение меню.
*/

#pragma once

/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"

#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UMenuWidget : public UUserWidget
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

	// Компонент кнопки увроней
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PlayLevelButton;

	// Компонент текст монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	// Компонент текст шарпы
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ShareTextCount;

	// Компонент текст очков
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	// Компонент изображения монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	// Компонент изображения шарпов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageShare;

protected:

	//////////////////////////
	//// Функции

	// Иницилизация виджета
	virtual void NativeConstruct() override;

	// Обновление виджета в каждом тике
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
