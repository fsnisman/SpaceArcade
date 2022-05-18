/*
*  Библеотеки
*/

#include "TriggerBoxSpawn.h"
#include "EnemyAIPawn.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

/*
*  Код
*/

// Инициализация объекта
ATriggerBoxSpawn::ATriggerBoxSpawn()
{
	// Динамическая проверка на пересечение с другими объектами
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxSpawn::OnOverlapBegin);
}

// Пересечение объекта 
void ATriggerBoxSpawn::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	// Цикл на проверку спав врагов с другими объектами полученные в мировом пространстве
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
