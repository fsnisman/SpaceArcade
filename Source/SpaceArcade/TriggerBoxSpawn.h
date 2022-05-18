/*
*	����� Trigger Box Spawn ����� ��� ������� ������ ������,
*	����� ��� �� ����������.
*/

#pragma once

/*
*  ����������
*/

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerBoxSpawn.generated.h"

/*
*  �����
*/

UCLASS()
class SPACEARCADE_API ATriggerBoxSpawn : public ATriggerBox
{
	GENERATED_BODY()

public:

	//////////////////////////
	//// �������

	// ������������� �������
	ATriggerBoxSpawn();

	// ������� �����������
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
};
