#pragma once

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

UCLASS()
class SPACEARCADE_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PauseButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* SpecialCannonButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* PlayerPBHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* BackgroundPlayerPBHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* PlayerTextPBHP;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* BossText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* FightText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberOneText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberTwoText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* NumberThreeText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageStart;
	
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageEnemy;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageVignette;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* VignetteAnimation;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* BossFightAnimation;

public:

	UFUNCTION()
		void OnButtonPauseGameClicked();

	UFUNCTION()
		void OnButtonSpecialCannonClicked();

protected:

	TWeakObjectPtr<APlayerShipPawn> OwnerPlayer;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	void SetHealt(float CurretHealth, float MaxHealth);

	bool UpdateWidget(float CurretHealth, float MaxHealth);
};
