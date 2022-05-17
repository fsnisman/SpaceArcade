#include "GameWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGameWidget::OnButtonPauseGameClicked);
	}

	if (SpecialCannonButton)
	{
		//SpecialCannonButton->bIsEnabled = false;
		SpecialCannonButton->OnClicked.AddDynamic(this, &UGameWidget::OnButtonSpecialCannonClicked);
	}


	if (!playerShip)
	{
		return;
	}

	SetHealt(playerShip->GetCurretHealth(), playerShip->GetMaxHealth());
}

void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!playerShip)
	{
		return;
	}

	UpdateWidget(playerShip->GetCurretHealth(), playerShip->GetMaxHealth());
}

void UGameWidget::SetHealt(float CurretHealth, float MaxHealth)
{
	CurretHealth = MaxHealth;
	PlayerPBHP->SetPercent(CurretHealth);
}

void UGameWidget::OnButtonPauseGameClicked()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
}

bool UGameWidget::UpdateWidget(float CurretHealth, float MaxHealth)
{
	bool bWasDestroyed = false;
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	if (playerShip->TriggerVingget)
	{
		PlayAnimation(VignetteAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
		playerShip->TriggerVingget = false;
	}

	if (playerShip->SpawnTextFightBoss)
	{
		PlayAnimation(BossFightAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
		playerShip->OnRedyOfFire();
		playerShip->SpawnTextFightBoss = false;
	}

	float Percent = CurretHealth / MaxHealth;
	
	if (CurretHealth >= 0)
	{
		PlayerPBHP->SetPercent(Percent);
		PlayerTextPBHP->SetText(FText::AsNumber(playerState->PlayerHP));
	}
	else
	{
		PlayerPBHP->SetPercent(0);
		PlayerTextPBHP->SetText(FText::AsNumber(0));
	}

	CoinTextCount->SetText(FText::AsNumber(playerState->Coin));
	ScoreTextCount->SetText(FText::AsNumber(playerState->ScoreCount));
	EnemyTextCount->SetText(FText::AsNumber(playerState->EnemyCount));

	return false;
}

void UGameWidget::OnButtonSpecialCannonClicked()
{
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	playerShip->FireSpecial();
}