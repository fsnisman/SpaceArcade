/*
*	Библеотеки
*/

#include "UpgradeWidget.h"

/*
*  Код
*/

void UUpgradeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на меню"
	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UUpgradeWidget::OnButtonMenuClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на достижения"
	if (AchivmentButton)
	{
		AchivmentButton->OnClicked.AddDynamic(this, &UUpgradeWidget::OnButtonAchivmentGameClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки улучшения урона"
	if (UpgradeButtonDamage)
	{
		UpgradeButtonDamage->OnClicked.AddDynamic(this, &UUpgradeWidget::OnUpgradeButtonDamageClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки улучшение здоровья"
	if (UpgradeButtonHealht)
	{
		UpgradeButtonHealht->OnClicked.AddDynamic(this, &UUpgradeWidget::OnUpgradeButtonHealhtClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки улучшения перезарядки"
	if (UpgradeButtonReloadSpecialCannon)
	{
		UpgradeButtonReloadSpecialCannon->OnClicked.AddDynamic(this, &UUpgradeWidget::OnUpgradeButtonReloadSpecialCannonClicked);
	}
}

void UUpgradeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Измнение значение виджетов
	CoinTextCount->SetText(FText::AsNumber(GameInstance->CoinOfPlayer));
	ShareTextCount->SetText(FText::AsNumber(GameInstance->ShardOfPlayer));

	// Цикл на проверку уровня улучшение урона
	if (CheakBuyDamageUpgrade)
	{
		// Обнуление стоимости
		CostDamageUpgrade = 0;
		for (int i = 0; i < GameInstance->LevelUpgradeDamage; i++)
		{
			// Прибавить стоимость к улучшению
			CostDamageUpgrade += 500;
		}
		// Обновление покупки
		CheakBuyDamageUpgrade = false;
	}
	// Цикл на проверку уровня улучшение здоровья
	if (CheakBuyHealhtUpgrade)
	{
		// Обнуление стоимости
		CostHealhtUpgrade = 0;
		for (int i = 0; i < GameInstance->LevelUpgradeHealht; i++)
		{
			// Прибавить стоимость к улучшению
			CostHealhtUpgrade += 500;
		}
		// Обновление покупки
		CheakBuyHealhtUpgrade = false;
	}
	// Цикл на проверку уровня улучшение перезарядки спец умения
	if (CheakBuyReloadSpecialCannonUpgrade)
	{
		// Обнуление стоимости
		CostReloadSpecialCannonUpgrade = 0;
		for (int i = 0; i < GameInstance->LevelUpgradeReloadSpecialCannon; i++)
		{
			// Прибавить стоимость к улучшению
			CostReloadSpecialCannonUpgrade += 500;
		}
		// Обновление покупки
		CheakBuyReloadSpecialCannonUpgrade = false;
	}

	// Измнение значение виджетов
	CostDamageUpgradeTextCount->SetText(FText::AsNumber(CostDamageUpgrade));
	CostHealhtUpgradeTextCount->SetText(FText::AsNumber(CostHealhtUpgrade));
	CostReloadSpecialCannonUpgradeTextCount->SetText(FText::AsNumber(CostReloadSpecialCannonUpgrade));
	LevelMaxDamageUpgradeTextCount->SetText(FText::AsNumber(GameInstance->LevelUpgradeDamage));
	LevelMaxHealhtUpgradeTextCount->SetText(FText::AsNumber(GameInstance->LevelUpgradeHealht));
	LevelMaxReloadSpecialCannonUpgradeTextCount->SetText(FText::AsNumber(GameInstance->LevelUpgradeReloadSpecialCannon));
}

// Нажатие кнопки на вызов виджета Meny
void UUpgradeWidget::OnButtonMenuClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::MainMenu);
}

// Нажатие кнопки на вызов виджета Achivement
void UUpgradeWidget::OnButtonAchivmentGameClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::AchievementsMenu);
}

// Функция для нажитии кнопки улучшения урона
void UUpgradeWidget::OnUpgradeButtonDamageClicked()
{
	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Проверка на количество монет и максимальный уровень
	if (GameInstance->CoinOfPlayer >= CostDamageUpgrade && GameInstance->LevelUpgradeDamage < GameInstance->LevelUpgradeDamageMax)
	{
		// Обновление покупки
		CheakBuyDamageUpgrade = true;
		// Добавление уровня
		GameInstance->LevelUpgradeDamage += 1;
		// Добавление значение урона
		GameInstance->UpgradeDamage += 0.1f;
		// Вычитание денег
		GameInstance->CoinOfPlayer -= CostDamageUpgrade;
	}
}

// Функция для нажитии кнопки улучшение здоровья
void UUpgradeWidget::OnUpgradeButtonHealhtClicked()
{
	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Проверка на количество монет и максимальный уровень
	if (GameInstance->CoinOfPlayer >= CostHealhtUpgrade && GameInstance->LevelUpgradeHealht < GameInstance->LevelUpgradeHealhtMax)
	{
		// Обновление покупки
		CheakBuyHealhtUpgrade = true;
		// Добавление уровня
		GameInstance->LevelUpgradeHealht += 1;
		// Добавление значение здоровья
		GameInstance->UpgradeHealht += 0.1f;
		// Вычитание денег
		GameInstance->CoinOfPlayer -= CostHealhtUpgrade;
	}
}

// Функция для нажитии кнопки улучшения перезарядки
void UUpgradeWidget::OnUpgradeButtonReloadSpecialCannonClicked()
{
	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Проверка на количество монет и максимальный уровень
	if (GameInstance->CoinOfPlayer >= CostReloadSpecialCannonUpgrade && GameInstance->LevelUpgradeReloadSpecialCannon < GameInstance->LevelUpgradeReloadSpecialCannonMax)
	{
		// Обновление покупки
		CheakBuyReloadSpecialCannonUpgrade = true;
		// Добавление уровня
		GameInstance->LevelUpgradeReloadSpecialCannon += 1;
		// Добавление значение перезарядки
		GameInstance->UpgradeReloadSpecialCannon += 0.1f;
		// Вычитание денег
		GameInstance->CoinOfPlayer -= CostReloadSpecialCannonUpgrade;
	}
}




