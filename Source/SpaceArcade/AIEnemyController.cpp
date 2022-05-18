/*
*  Библеотеки
*/

#include "AIEnemyController.h"
#include "EnemyAIPawn.h"
#include "Kismet/KismetMathLibrary.h"

/*
*  Код
*/

// Начало действия при создании объекта
void AAIEnemyController::BeginPlay()
{
    Super::BeginPlay();
    // Иницилизация
    Initalize();
}

// Обновление объекта в каждом тике
void AAIEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Проверка на контроллер
    if (!EnemyShipAIPawn)
    {
        // Иницилизация
        Initalize();
    }

    // Проверка на контроллер
    if (!EnemyShipAIPawn)
    {
        return;
    }

    // Проверка на нулевые точки патруля
    if (CurrentPatrolPointIndex == INDEX_NONE)
    {
        // Остановить движение
        EnemyShipAIPawn->FMovementComponent(0.f);
        return;
    }

    // Проверка на остановку движеня
    if (EnemyShipAIPawn->tbStoppedMove)
    {
        // Проверка на первую точку патруля
        if (CurrentPatrolPointIndex == 1)
        {
            // Остановить корабль
            EnemyShipAIPawn->StopMove();
            return;
        }
    }

    // Проверка на наличие тега "Boss"
    if (EnemyShipAIPawn->ActorHasTag(TEXT("Boss")))
    {
        // Проверка на первую точку патруля
        if (CurrentPatrolPointIndex == 1)
        {
            // Остановить корабль
            EnemyShipAIPawn->FMovementComponent(0.f);
            return;
        }
    }

    // Придать движение кораблю
    EnemyShipAIPawn->FMovementComponent(1.f);

    // Значение поворота
    float rotationValue = GetRotationgValue();
    // Задать значение поворота
    EnemyShipAIPawn->FRotationComponent(rotationValue);
}

// Иницилизация
void AAIEnemyController::Initalize()
{
    // Каст на пешку врага
    EnemyShipAIPawn = Cast<AEnemyAIPawn>(GetPawn());

    // Проверка
    if (EnemyShipAIPawn)
    {
        // Каста на игрока
        PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
        // Получение значение частоты движения
        MovementAccurancy = EnemyShipAIPawn->GetMovementAccurancy();
        // Получение точек патруля
        PatrollingPoints = EnemyShipAIPawn->GetPatrollingPoints();
    }

    // Присвоить точки патруля к текущему значеню точек
    CurrentPatrolPointIndex = PatrollingPoints.Num() == 0 ? INDEX_NONE : 0;
}

// Получение значение поворота на следующую точку
float AAIEnemyController::GetRotationgValue()
{
    // Каст на игрока
    APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
    // Текущее значение точек
    FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
    // Текущие месторасположение пешки врага
    FVector pawnLocation = EnemyShipAIPawn->GetActorLocation();
    // Проверка на расстояние от пешки до точки
    if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurancy)
    {
        // Инктрементация текущего значение точку
        CurrentPatrolPointIndex++;
        // Проверка на превышение текушего значение точек от массива точке
        if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
        {
            // Проверка на наличие тега "Boss"
            if (!EnemyShipAIPawn->ActorHasTag(TEXT("Boss")))
            {
                // Проверка на игрока
                if (PlayerShip)
                {
                    // Прибавить значение уничтоженных врагов
                    PlayerShip->CountDiedEnemyPawn++;
                }
                // Уничтожить пешку
                EnemyShipAIPawn->Destroy();
            }
        }
    }

    // Расстояние от текущей точки до пешки врага
    FVector moveDirection = currentPoint - pawnLocation;
    // Нормалайз расстояния
    moveDirection.Normalize();
    // Значение локации пешки
    FVector forwardDirection = EnemyShipAIPawn->GetActorForwardVector();
    // Значение поворота пешки
    FVector rightDirection = EnemyShipAIPawn->GetActorRightVector();

    // Высчитать значение поворота
    float forwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(forwardDirection, moveDirection)));
    float rightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(rightDirection, moveDirection)));

    float rotationValue = 0;

    // Проверка на движения прямо
    if (forwardAngle > 5.f)
    {
        rotationValue = 1.f;
    }
    // Проверка на поворт корабля
    if (rightAngle > 90)
    {
        rotationValue = -rotationValue;
    }

    return rotationValue;
}