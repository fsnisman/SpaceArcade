#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHud.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	None,
	MainMenu,
	PauseMenu,
	GameInteface,
	UpgradeMenu,
	LevelMenu,
	GameOverMenu,
	LoadingWidget,
	VictoryTextWidget,
	StateVictoryWidget,
	AchievementsMenu
};

UCLASS()
class SPACEARCADE_API AGameHud : public AHUD
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
		TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClases;

	UPROPERTY()
		UUserWidget* CurrentWidget;

	EWidgetID CurrentWidgetID;

public:

	void BeginPlay() override;
	void RemoveCurrentWidgetFromViewport();

	UFUNCTION(BlueprintCallable)
	UUserWidget* UseWidget(EWidgetID widgetID, bool RemovePrevious = true, int32 ZOrder = 0);

	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget();

	UFUNCTION(BlueprintCallable)
	UUserWidget* AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder = 0);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bPause;
};
