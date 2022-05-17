#include "PuaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UPuaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(Animation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);

	SNameLevel = UGameplayStatics::GetCurrentLevelName(this, bRemovePrefixString);
	NameLevel = FName(*SNameLevel);

	if (PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonPlayGameClicked);
	}

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonRestartGameClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UPuaseWidget::OnButtonExitGameClicked);
	}
}

void UPuaseWidget::OnButtonRestartGameClicked()
{
	UGameplayStatics::OpenLevel(this, NameLevel);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void UPuaseWidget::OnButtonPlayGameClicked()
{
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}

void UPuaseWidget::OnButtonExitGameClicked()
{
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
