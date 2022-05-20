/*
*	Класс Upgrade Widget для отображение улучшение корабля.
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


#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeWidget.generated.h"

/*
*  Класс
*/

UCLASS()
class SPACEARCADE_API UUpgradeWidget : public UUserWidget
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

	// Компонент кнопки улучшения урона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* UpgradeButtonDamage;

	// Компонент кнопки улучшения здоровья
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* UpgradeButtonHealht;

	// Компонент кнопки улучшения перезарядки
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* UpgradeButtonReloadSpecialCannon;

	// Компонент текст монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	// Компонент текст шарпы
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ShareTextCount;

	// Компонент текст стоимости улучшение урона
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CostDamageUpgradeTextCount;

	// Компонент текст стоимости улучшение здоровья
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CostHealhtUpgradeTextCount;

	// Компонент текст стоимости улучшение перезаридки ульты
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CostReloadSpecialCannonUpgradeTextCount;

	// Компонент текст стоимости улучшение перезаридки ульты
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* LevelMaxDamageUpgradeTextCount;

	// Компонент текст стоимости улучшение перезаридки ульты
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* LevelMaxHealhtUpgradeTextCount;

	// Компонент текст стоимости улучшение перезаридки ульты
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* LevelMaxReloadSpecialCannonUpgradeTextCount;

	// Компонент изображения монет
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	// Компонент изображения шарпов
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageShare;

protected:

	//////////////////////////
	//// Функции

	// Функция для нажитии кнопки перехода на меню
	UFUNCTION()
		void OnButtonMenuClicked();

	// Функция для нажитии кнопки перехода на достижения
	UFUNCTION()
		void OnButtonAchivmentGameClicked();

	// Функция для нажитии кнопки улучшения урона
	UFUNCTION()
		void OnUpgradeButtonDamageClicked();

	// Функция для нажитии кнопки улучшение здоровья
	UFUNCTION()
		void OnUpgradeButtonHealhtClicked();

	// Функция для нажитии кнопки улучшения перезарядки
	UFUNCTION()
		void OnUpgradeButtonReloadSpecialCannonClicked();

	// Иницилизация виджета
	virtual void NativeConstruct() override;

	// Обновление виджета в каждом тике
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//////////////////////////
	//// Переменные

	// Стоимость улучшение урона
	int CostDamageUpgrade = 0;
	// Стоимоить улчешине здоровья
	int CostHealhtUpgrade = 0;
	// Стоимость улучшение перезарядки ульты
	int CostReloadSpecialCannonUpgrade = 0;

	// Проверка на покупку улучшение урона
	bool CheakBuyDamageUpgrade = true;
	// Проверка на покупку улучшение здоровья
	bool CheakBuyHealhtUpgrade = true;
	// Проверка на покупку улучшение перезарядки ульты
	bool CheakBuyReloadSpecialCannonUpgrade = true;
};
