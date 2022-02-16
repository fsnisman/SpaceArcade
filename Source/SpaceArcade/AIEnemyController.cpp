
#include "AIEnemyController.h"
#include "EnemyAIPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void AAIEnemyController::BeginPlay()
{
    Super::BeginPlay();
    Initalize();
}

void AAIEnemyController::Initalize()
{
    EnemyShipAIPawn = Cast<AEnemyAIPawn>(GetPawn());

    if (EnemyShipAIPawn)
    {
        PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

        FVector pawnLocation = EnemyShipAIPawn->GetActorLocation();
        MovementAccurancy = EnemyShipAIPawn->GetMovementAccurancy();
        TArray<FVector> points = EnemyShipAIPawn->GetPatrollingPoints();

        for (FVector point : points)
        {
            PatrollingPoints.Add(point + pawnLocation);
        }

        CurrentPatrolPointIndex = PatrollingPoints.Num() == 0 ? INDEX_NONE : 0;
    }
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

    EnemyShipAIPawn->FMovementComponent(1.f);

    float rotationValue = GetRotationgValue();
    EnemyShipAIPawn->FRotationComponent(rotationValue);

    
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
            Destroy();
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

//void AAIEnemyController::Targeting()
//{
//    /*if (CanFire())
//    {
//        Fire();
//    }
//    else
//    {
//        RotateToPlayer();
//    }*/
//}
//
//
//void AAIEnemyController::RotateToPlayer()
//{
//    if (IsPlayerInRange() && PlayerPawn)
//    {
//        EnemyShipAIPawn->RotateArrowTo(PlayerPawn->GetActorLocation());
//    }
//}
//
//bool AAIEnemyController::IsPlayerInRange()
//{
//    if (PlayerPawn)
//    {
//        return FVector::Distance(EnemyShipAIPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
//    }
//    return false;
//}
//
//bool AAIEnemyController::IsPlayerSeen()
//{
//    if (PlayerPawn)
//    {
//        FVector playerPos = PlayerPawn->GetActorLocation();
//        FVector eyesPos = EnemyShipAIPawn->GetEyesPosition();
//
//        FHitResult hitResult;
//        FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
//        traceParams.bTraceComplex = true;
//        traceParams.AddIgnoredActor(EnemyShipAIPawn);
//        traceParams.bReturnPhysicalMaterial = false;
//
//        if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams))
//        {
//
//            if (hitResult.Actor.Get())
//            {
//                DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
//                return hitResult.Actor.Get() == PlayerPawn;
//            }
//        }
//        DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10);
//        return false;
//    }
//    return false;
//}
//
//bool AAIEnemyController::CanFire()
//{
//    if (!IsPlayerSeen())
//    {
//        return false;
//    }
//
//    FVector targetingDir = EnemyShipAIPawn->GetArrowForwardVector();
//    FVector dirToPlayer = PlayerPawn->GetActorLocation() - EnemyShipAIPawn->GetActorLocation();
//    dirToPlayer.Normalize();
//    float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
//    return aimAngle <= Accuracy;
//}
//
//void AAIEnemyController::Fire()
//{
//    //EnemyShipAIPawn->Fire();
//}
