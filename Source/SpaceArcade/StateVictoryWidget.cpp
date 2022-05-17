#include "StateVictoryWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UStateVictoryWidget::NativeConstruct()
{
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	if (MenuBackButton)
	{
		MenuBackButton->OnClicked.AddDynamic(this, &UStateVictoryWidget::OnButtonMenuBackClicked);
	}

	
	for (int i = 0; Coin <= playerState->Coin; i++)
	{
		Coin++;
		CoinTextCount->SetText(FText::AsNumber(Coin));
	}
	
	for (int i = 0; Score <= playerState->iScore; i++)
	{
		Score++;
		ScoreTextCount->SetText(FText::AsNumber(Score));
	}
	
	for (int i = 0; Enemy <= playerState->EnemyCount; i++)
	{
		Enemy++;
		EnemyTextCount->SetText(FText::AsNumber(Enemy));
	}
}

void UStateVictoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	
}

void UStateVictoryWidget::OnButtonMenuBackClicked()
{
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
