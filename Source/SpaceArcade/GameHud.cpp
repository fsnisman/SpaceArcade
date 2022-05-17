#include "GameHud.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AGameHud::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, nullptr, EMouseLockMode::DoNotLock, false);
				PC->bShowMouseCursor = true;
			}
	}

}

UUserWidget* AGameHud::GetCurrentWidget()
{
	return CurrentWidget;

}

void AGameHud::RemoveCurrentWidgetFromViewport()
{
	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
		CurrentWidgetID = EWidgetID::None;
	}

}


UUserWidget* AGameHud::AddWidgetToViewportByClass(TSubclassOf<UUserWidget> WidgetClass, int32 ZOrder)
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	
	if (CurrentWidget)
	{
		CurrentWidget->AddToViewport(ZOrder);
	}

	return CurrentWidget;
}


UUserWidget* AGameHud::UseWidget(EWidgetID widgetID, bool RemovePrevious, int32 ZOrder)
{
	if (CurrentWidgetID == widgetID)
	{
		return CurrentWidget;
	}

	if (RemovePrevious)
	{
		RemoveCurrentWidgetFromViewport();
	}

	TSubclassOf<UUserWidget> WidgetClassToUse = WidgetClases.FindRef(widgetID);
	
	if (WidgetClassToUse.Get())
	{
		CurrentWidgetID = widgetID;
		return AddWidgetToViewportByClass(WidgetClassToUse, ZOrder);
	}

	return nullptr;
}