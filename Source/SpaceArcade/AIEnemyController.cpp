
#include "AIEnemyController.h"
#include "EnemyAIPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void AAIEnemyController::BeginPlay()
{
    Super::BeginPlay();
    Initalize();
}

void AAIEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!EnemyShipAIPawn)
    {
        Initalize();
    }

    if (!EnemyShipAIPawn)
    {
        return;
    }

    if (CurrentPatrolPointIndex == INDEX_NONE)
    {
        EnemyShipAIPawn->FMovementComponent(0.f);
        return;
    }

    if (EnemyShipAIPawn->ActorHasTag(TEXT("Boss")))
    {
        if (CurrentPatrolPointIndex == 1)
        {
            EnemyShipAIPawn->FMovementComponent(0.f);
            return;
        }
    }


    EnemyShipAIPawn->FMovementComponent(1.f);

    float rotationValue = GetRotationgValue();
    EnemyShipAIPawn->FRotationComponent(rotationValue);
}

void AAIEnemyController::Initalize()
{
    EnemyShipAIPawn = Cast<AEnemyAIPawn>(GetPawn());

    if (EnemyShipAIPawn)
    {
        PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
        MovementAccurancy = EnemyShipAIPawn->GetMovementAccurancy();
        PatrollingPoints = EnemyShipAIPawn->GetPatrollingPoints();
    }

    CurrentPatrolPointIndex = PatrollingPoints.Num() == 0 ? INDEX_NONE : 0;
}


float AAIEnemyController::GetRotationgValue()
{
    FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
    FVector pawnLocation = EnemyShipAIPawn->GetActorLocation();
    if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurancy)
    {
        CurrentPatrolPointIndex++;
        if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
        {
            EnemyShipAIPawn->Destroy();
        }
    }

    FVector moveDirection = currentPoint - pawnLocation;
    moveDirection.Normalize();
    FVector forwardDirection = EnemyShipAIPawn->GetActorForwardVector();
    FVector rightDirection = EnemyShipAIPawn->GetActorRightVector();

    DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Green, false, 0.1f, 0, 5);

    float forwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(forwardDirection, moveDirection)));
    float rightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(rightDirection, moveDirection)));

    float rotationValue = 0;

    if (forwardAngle > 5.f)
    {
        rotationValue = 1.f;
    }
    if (rightAngle > 90)
    {
        rotationValue = -rotationValue;
    }

    return rotationValue;
}
