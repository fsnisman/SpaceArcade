#pragma once

#include "PlayerShipPawn.h"

#include "Components/CanvasPanel.h"
#include "Components/GridPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

UCLASS()
class SPACEARCADE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UGridPanel* GridPanelButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* MenuButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* UpgradeButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* AchivmentButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PlayLevelButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* CoinTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ShareTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* ScoreTextCount;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageCoin;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* ImageShare;

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
