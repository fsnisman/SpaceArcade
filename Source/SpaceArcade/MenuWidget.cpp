/*
*	Библеотеки
*/

#include "MenuWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

/*
*  Код
*/

// Иницилизация виджета
void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Меню виджет активный
	bMenuWidget = true;
	playerShip->bActiveMenuWidget = bMenuWidget;

	// Динамическая инициализация функции "Функция для нажитии кнопки воспроизведния игры"
	if (PlayLevelButton)
	{
		PlayLevelButton->OnClicked.AddDynamic(this, &UMenuWidget::OnButtonPlayGameClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на улучшение"
	if (UpgradeButton)
	{
		UpgradeButton->OnClicked.AddDynamic(this, &UMenuWidget::OnButtonUpgradeClicked);
	}

	// Динамическая инициализация функции "Функция для нажитии кнопки перехода на достижения"
	if (AchivmentButton)
	{
		AchivmentButton->OnClicked.AddDynamic(this, &UMenuWidget::OnButtonAchivmentGameClicked);
	}
}

// Обновление виджета каждый тик
void UMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Измнение значение виджетов
	CoinTextCount->SetText(FText::AsNumber(GameInstance->CoinOfPlayer));
	ShareTextCount->SetText(FText::AsNumber(GameInstance->ShardOfPlayer));
	ScoreTextCount->SetText(FText::AsNumber(GameInstance->ScoreOfPlayre));
}

// Нажатие кнопки запуска уровня
void UMenuWidget::OnButtonPlayGameClicked()
{
	// Открыть игровой уровень
	UGameplayStatics::OpenLevel(this, "Level1");
	// Удалить виджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

// Нажатие кнопки на вызов виджета Upgrade
void UMenuWidget::OnButtonUpgradeClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::UpgradeMenu);
}

// Нажатие кнопки на вызов виджета Achivement
void UMenuWidget::OnButtonAchivmentGameClicked()
{
	// Каст на худ
	AGameHud* HUD = Cast<AGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	// Использование виджета
	HUD->UseWidget(EWidgetID::AchievementsMenu);
}