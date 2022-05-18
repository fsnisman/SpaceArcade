/*
*  ����������
*/

#include "TriggerBoxSpawn.h"
#include "EnemyAIPawn.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

/*
*  ���
*/

// ������������� �������
ATriggerBoxSpawn::ATriggerBoxSpawn()
{
	// ������������ �������� �� ����������� � ������� ���������
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxSpawn::OnOverlapBegin);
}

// ����������� ������� 
void ATriggerBoxSpawn::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// ���� �� �������� ���� ������ � ������� ��������� ���������� � ������� ������������
	for (TActorIterator<AEnemyAIPawn> EnemyItr(GetWorld()); EnemyItr; ++EnemyItr)
	{
		AEnemyAIPawn* EnemyActor = *EnemyItr;

		if (OtherActor == EnemyActor)
		{
			break;
		}
		else
		{
			break;
		}
	}
}
