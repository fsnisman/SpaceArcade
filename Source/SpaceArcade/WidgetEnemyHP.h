#pragma once

#include "EnemyAIPawn.h"

#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEnemyHP.generated.h"

UCLASS()
class SPACEARCADE_API UWidgetEnemyHP : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<AEnemyAIPawn> OwnerEnemy;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* EnemyBarHP;

public:

	void SetHealt(float CurretHealth, float MaxHealth);

	bool UpdateHealth(float CurretHealth, float MaxHealth);

	void SetOwner(AEnemyAIPawn* InEnemy){ OwnerEnemy = InEnemy; }
};
