#include "GameOverWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(Animation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f, false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);

	SNameLevel = UGameplayStatics::GetCurrentLevelName(this, bRemovePrefixString);
	NameLevel = FName(*SNameLevel);

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonRestartGameClicked);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UGameOverWidget::OnButtonExitGameClicked);
	}
}

void UGameOverWidget::OnButtonRestartGameClicked()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	UGameplayStatics::OpenLevel(this, NameLevel);
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}

void UGameOverWidget::OnButtonExitGameClicked()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
	UGameplayStatics::OpenLevel(this, "MenuLevel");
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
}
