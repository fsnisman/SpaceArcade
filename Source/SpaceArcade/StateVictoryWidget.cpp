/*
*  Библеотеки
*/

#include "StateVictoryWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

/*
*  Код
*/

// Инициализация виджета
void UStateVictoryWidget::NativeConstruct()
{
	// Каст на пешку игрока и данных игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	// Динамическая инициализация функции "Нажатие на кнопку возращение в меню"
	if (MenuBackButton)
	{
		MenuBackButton->OnClicked.AddDynamic(this, &UStateVictoryWidget::OnButtonMenuBackClicked);
	}

	// Инициализация подсчета монет от общего значения данных у игрока
	for (int i = 0; Coin <= playerState->Coin; i++)
	{
		Coin++;
		CoinTextCount->SetText(FText::AsNumber(Coin));
	}

	// Инициализация подсчета очков от общего значения данных у игрока
	for (int i = 0; Score <= playerState->iScore; i++)
	{
		Score++;
		ScoreTextCount->SetText(FText::AsNumber(Score));
	}
	
	// Инициализация подсчета врагов от общего значения данных у игрока
	for (int i = 0; Enemy <= playerState->EnemyCount; i++)
	{
		Enemy++;
		EnemyTextCount->SetText(FText::AsNumber(Enemy));
	}

	// Каст на глобальную информацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Изменения значний в глобальной информации
	GameInstance->ScoreOfPlayre += Score;
	GameInstance->CoinOfPlayer += Coin;
	GameInstance->EnemyDiedCountOfPlayer += playerState->EnemyCount;
}

// Нажатие на кнопку возращение в меню
void UStateVictoryWidget::OnButtonMenuBackClicked()
{
	// Открыть уровень меню
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	// Удалить все выджеты
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
