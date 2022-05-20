/*
*	Библеотеки
*/

#include "AchivmentWidget.h"

/*
*  Код
*/

void UAchivmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на меню"
	if (MenuButton)
	{
		MenuButton->OnClicked.AddDynamic(this, &UAchivmentWidget::OnButtonMenuClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на улучшение"
	if (UpgradeButton)
	{
		UpgradeButton->OnClicked.AddDynamic(this, &UAchivmentWidget::OnButtonUpgradeClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки получение приза за полученные очки"
	if (GetPrizeScoreButton)
	{
		GetPrizeScoreButton->OnClicked.AddDynamic(this, &UAchivmentWidget::OnGetPrizeScoreButtonClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки получение приза за уничтоженных врагов"
	if (GetPrizeEnemyButton)
	{
		GetPrizeEnemyButton->OnClicked.AddDynamic(this, &UAchivmentWidget::OnGetPrizeEnemyButtonClicked);
	}
}

void UAchivmentWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Записть значение заработанных очков
	float PercentScore = GameInstance->ScoreOfPlayre / GameInstance->ChallengeScoreMax;
	// Записть значение уничтоженных врагов
	float PercentEnemy = GameInstance->EnemyDiedCountOfPlayer / GameInstance->ChallengeEnemyDiedMax;

	// Измнение значение виджетов
	CoinTextCount->SetText(FText::AsNumber(GameInstance->CoinOfPlayer));
	ShareTextCount->SetText(FText::AsNumber(GameInstance->ShardOfPlayer));

	// Измненеие значение в компонентах
	PrizeScorePB->SetPercent(PercentScore);
	PrizeEnemyPB->SetPercent(PercentEnemy);
	EarnedScoreTextCount->SetText(FText::AsNumber(GameInstance->ScoreOfPlayre));
	EarnedEnemyTextCount->SetText(FText::AsNumber(GameInstance->EnemyDiedCountOfPlayer));
	EarnedScoreTextCountMax->SetText(FText::AsNumber(GameInstance->ChallengeScoreMax));
	EarnedEnemyTextCountMax->SetText(FText::AsNumber(GameInstance->ChallengeEnemyDiedMax));
}

void UAchivmentWidget::OnGetPrizeScoreButtonClicked()
{
	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Проверка на заработанные очки
	if (GameInstance->ScoreOfPlayre >= GameInstance->ChallengeScoreMax)
	{
		// Получить приз
		GameInstance->CoinOfPlayer += Prize;
		// Увеличить значение челледжа
		GameInstance->ChallengeScoreMax += 1500;
	}
}

void UAchivmentWidget::OnGetPrizeEnemyButtonClicked()
{
	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Проверка на заработанные очки
	if (GameInstance->EnemyDiedCountOfPlayer >= GameInstance->ChallengeEnemyDiedMax)
	{
		// Получить приз
		GameInstance->CoinOfPlayer += Prize;
		// Увеличить значение челледжа
		GameInstance->ChallengeEnemyDiedMax += 100;
	}
}

// Нажатие кнопки на вызов виджета Meny
void UAchivmentWidget::OnButtonMenuClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::MainMenu);
}

// Нажатие кнопки на вызов виджета Upgrade
void UAchivmentWidget::OnButtonUpgradeClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::UpgradeMenu);
}