/*
*	����� Widget Enemy HP ��� ����������� �������� ������
*	������� ������������.
*/

#pragma once

/*
*  ����������
*/

#include "EnemyAIPawn.h"

#include "Components/ProgressBar.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetEnemyHP.generated.h"

/*
*  �����
*/

UCLASS()
class SPACEARCADE_API UWidgetEnemyHP : public UUserWidget
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// ����������

	// ��������� �������� ����
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
		UProgressBar* EnemyBarHP;

	//////////////////////////
	//// �������

	// ������������� �������
	virtual void NativeConstruct() override;

	// ���������� ������� ������ ������� ���
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//////////////////////////
	//// ����������

	// ������ ������
	TWeakObjectPtr<AEnemyAIPawn> OwnerEnemy;

public:

	//////////////////////////
	//// �������

	// ��������� �������� ������
	void SetHealt(float CurretHealth, float MaxHealth);

	// ���������� ��������
	bool UpdateHealth(float CurretHealth, float MaxHealth);

	// ��������� ������� �� �����
	void SetOwner(AEnemyAIPawn* InEnemy){ OwnerEnemy = InEnemy; }
};
