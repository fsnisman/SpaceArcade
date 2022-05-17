#pragma once

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/BackgroundBlur.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PuaseWidget.generated.h"


UCLASS()
class SPACEARCADE_API UPuaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UCanvasPanel* MainCanvasPanel;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UBackgroundBlur* BackgroundUI;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UImage* BackgroundPause;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* RestartButton;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UButton* ExitButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* Animation;

public:
	
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnButtonRestartGameClicked();
	
	UFUNCTION()
		void OnButtonPlayGameClicked();

	UFUNCTION()
		void OnButtonExitGameClicked();

public:

	FName NameLevel;
	FString SNameLevel;

	bool bRemovePrefixString = true;
};
