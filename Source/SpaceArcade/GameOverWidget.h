#pragma once

#include "PlayerShipPawn.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

UCLASS()
class SPACEARCADE_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* RestartButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* ExitButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UTextBlock* GameOver;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* BackgroundUI;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UBackgroundBlur* BackgroundBlurUI;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Animation;

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnButtonRestartGameClicked();

	UFUNCTION()
		void OnButtonExitGameClicked();

public:

	FName NameLevel;
	FString SNameLevel;

	bool bRemovePrefixString = true;
};
