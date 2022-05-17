#pragma once

#include "PlayerShipPawn.h"

#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StateVictoryWidget.generated.h"

UCLASS()
class SPACEARCADE_API UStateVictoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* MenuBackButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyText;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* EnemyTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageEnemy;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageBackground;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UFUNCTION()
		void OnButtonMenuBackClicked();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Score = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Coin = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Enemy = 0;
};
