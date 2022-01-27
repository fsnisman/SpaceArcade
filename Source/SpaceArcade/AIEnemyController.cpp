
#include "AIEnemyController.h"
#include "EnemyAIPawn.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "DrawDebugHelpers.h"

void AAIEnemyController::BeginPlay()
{
    Super::BeginPlay();
    
    EnemyShipAIPawn = Cast<AEnemyAIPawn>(GetPawn());

    FVector pawnLocation = EnemyShipAIPawn->GetActorLocation();
    MovementAccurancy = EnemyShipAIPawn->GetMovementAccurancy();
    TArray<FVector> points = EnemyShipAIPawn->GetPatrollingPoints();
    for (FVector point : points)
    {
        PatrollingPoints.Add(point + pawnLocation);
    }
    CurrentPatrolPointIndex = PatrollingPoints.Num() == 0 ? INDEX_NONE : 0;
}

void AAIEnemyController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (CurrentPatrolPointIndex == INDEX_NONE)
    {
        EnemyShipAIPawn->FMovementComponent();
        return;
    }

    EnemyShipAIPawn->FMovementComponent();

    bool CheckRotation = false;

    FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
    FVector pawnLocation = EnemyShipAIPawn->GetActorLocation();
    if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccurancy)
    {
        CheckRotation = true;
        CurrentPatrolPointIndex++;
        if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
        {
            CurrentPatrolPointIndex = 0;
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

    //UE_LOG(LogTemp, Warning, TEXT("AI Rotation forwardAngle: %f rightAngle: %f rotationValue: %f"), forwardAngle, rightAngle, rotationValue);
    
    /*if (CheckRotation == true)
    {
        EnemyShipAIPawn->FRotationComponent(1.f);
    }
    else
    {
        EnemyShipAIPawn->FRotationComponent(0.f);
    }*/

    EnemyShipAIPawn->FRotationComponent(rotationValue);
}
