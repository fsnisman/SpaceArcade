/*
*  Библеотеки
*/

#include "GameWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"

/*
*  Код
*/

// Иницилизация объекта
void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Динамическая инициализация функции "Нажатие на кнопку паузы"
	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGameWidget::OnButtonPauseGameClicked);
	}

	// Динамическая инициализация функции "Нажатие на кнопку особого орудия"
	if (SpecialCannonButton)
	{
		//x SpecialCannonButton->bIsEnabled = false;

		SpecialCannonButton->OnClicked.AddDynamic(this, &UGameWidget::OnButtonSpecialCannonClicked);
	}

	// Проверка на каст игрока
	if (!playerShip)
	{
		return;
	}

	// Установить значение здоровья игрока
	SetHealt(playerShip->GetCurretHealth(), playerShip->GetMaxHealth());
}

// Обновление объекта на каждый тик
void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Проверка на каст
	if (!playerShip)
	{
		return;
	}

	// Обновление виджета
	UpdateWidget(playerShip->GetCurretHealth(), playerShip->GetMaxHealth());
}

// Установить значение здоровья
void UGameWidget::SetHealt(float CurretHealth, float MaxHealth)
{
	// Текущие значение здровья присвоить максимальное значение
	CurretHealth = MaxHealth;
	PlayerPBHP->SetPercent(CurretHealth);
}

// Нажатие на кнопку паузы
void UGameWidget::OnButtonPauseGameClicked()
{
	// Остановить игровое время
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
}

// Обновление виджета
bool UGameWidget::UpdateWidget(float CurretHealth, float MaxHealth)
{
	bool bWasDestroyed = false;
	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Каст на данные игрока
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	// Проверка переменной 
	if (playerShip->TriggerVingget)
	{
		// Запуск анимации
		PlayAnimation(VignetteAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
		// Перезапись переменной
		playerShip->TriggerVingget = false;
	}

	// Проверка переменной
	if (playerShip->SpawnTextFightBoss)
	{
		// Запуск анимации
		PlayAnimation(BossFightAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
		// Запуск функции
		playerShip->OnRedyOfFire();
		// Перезаписть переменной
		playerShip->SpawnTextFightBoss = false;
	}

	// Записть значение здоровья текущего от максимального
	float Percent = CurretHealth / MaxHealth;

	// Проверка на текущее занчение здоровья
	if (CurretHealth >= 0)
	{
		// Уставноить значение в компонентах
		PlayerPBHP->SetPercent(Percent);
		PlayerTextPBHP->SetText(FText::AsNumber(playerState->PlayerHP));
	}
	else
	{
		// Уставноить значение в компонентах
		PlayerPBHP->SetPercent(0);
		PlayerTextPBHP->SetText(FText::AsNumber(0));
	}

	// Уставноить значение в компонентах
	CoinTextCount->SetText(FText::AsNumber(playerState->Coin));
	ScoreTextCount->SetText(FText::AsNumber(playerState->ScoreCount));
	EnemyTextCount->SetText(FText::AsNumber(playerState->EnemyCount));

	return false;
}

// Нажатие на кнопку особого орудия
void UGameWidget::OnButtonSpecialCannonClicked()
{
	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Запуск функции
	playerShip->FireSpecial();
}