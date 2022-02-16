
#include "EnemyAIPawn.h"

AEnemyAIPawn::AEnemyAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	//=========================
	// Create Static Mesh for Ship
	//=========================

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = BodyMesh;

	//=========================
	// Create Hit Colloder for Ship
	//=========================

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	//=========================
	// Create Spawn Arrow for ProjectTile
	//=========================

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(BodyMesh);

	//=========================
	// Create Health Component for Ship
	//=========================

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddDynamic(this, &AEnemyAIPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &AEnemyAIPawn::DamageTaked);

	//=========================
	// Create Shoot Effect for Cannon
	//=========================

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	//=========================
	// Create Fire Effect for Engine
	//=========================

	EngineEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect"));
	EngineEffect->SetupAttachment(BodyMesh);

	EngineEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect 2"));
	EngineEffect2->SetupAttachment(BodyMesh);

	//=========================
	// Create Line Fly Effect for Wings
	//=========================

	LineFlyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect"));
	LineFlyEffect->SetupAttachment(BodyMesh);

	LineFlyEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect 2"));
	LineFlyEffect2->SetupAttachment(BodyMesh);

	//=========================
	// Create Line Exlosion Effect
	//=========================

	ExlosionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Exlosion effect"));

	//=========================
	// Create Audio Effect for Cannon
	//=========================

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot audio effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPoint);
}

void AEnemyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	TimerFire();

	EngineEffect->ActivateSystem();
	EngineEffect2->ActivateSystem();
	LineFlyEffect->ActivateSystem();
	LineFlyEffect2->ActivateSystem();
}


void AEnemyAIPawn::TimerFire()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, FireRange, true, FireFrequency); //Timer for Shoot Fire
}

FVector AEnemyAIPawn::GetArrowForwardVector()
{
	return ProjectileSpawnPoint->GetForwardVector();
}

// Function for Monement Enemy Ship
float AEnemyAIPawn::FMovementComponent(float ValueAxis)
{
	if (ValueAxis == 0)
	{
		return TargetForwardAxisValue = ValueAxis;
	}
	else
	{
		return TargetForwardAxisValue = MoveSpeed;
	}

}

// Function for Rotation Enemy Ship
float AEnemyAIPawn::FRotationComponent(float ValueAxis)
{
	return TargetRightAxisValue = ValueAxis;
}

void AEnemyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentForwardAxisValue = FMath::FInterpTo(CurrentForwardAxisValue, TargetForwardAxisValue, DeltaTime, ForwardSmootheness);
	TargetForwardAxisValue = CurrentForwardAxisValue;

	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector MovePosition = CurrentLocation + ForwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;

	SetActorLocation(MovePosition, true);

	if (bTrackingPlayer)
	{

		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (PlayerShip)
		{
			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerShip->GetActorLocation());
			FRotator CurreRotation = ProjectileSpawnPoint->GetComponentRotation();
			TargetRotation.Pitch = CurreRotation.Pitch;
			TargetRotation.Roll = CurreRotation.Roll;
			ProjectileSpawnPoint->SetWorldRotation(FMath::RInterpConstantTo(CurreRotation, TargetRotation, DeltaTime, MovementAccurancy));
		}
	}

	FRotator CurrentRotation = GetActorRotation();
	float yawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
	yawRotation += CurrentRotation.Yaw;

	FRotator newRotation = FRotator(0.f, yawRotation, 0.f);

	SetActorRotation(newRotation);
}

void AEnemyAIPawn::RotateArrowTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator currRotation = ProjectileSpawnPoint->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	ProjectileSpawnPoint->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, MovementAccurancy));
}

FVector AEnemyAIPawn::GetEyesPosition()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

void AEnemyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Function for Health Point Enemy Ship
bool AEnemyAIPawn::TDamage(FDamageData DamageData)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageData.DamageValue, HealthComponent->GetHealth());
	return HealthComponent->TDamage(DamageData);
}

// Function for Die Enemy Ship
void AEnemyAIPawn::Die()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExlosionEffect, GetActorTransform());

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	Destroy();
}

// Finction for Track DamageTaked
void AEnemyAIPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

// Finction for Shoot Enemy Ship
void AEnemyAIPawn::Fire()
{
	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	FActorSpawnParameters ParamsI;
	ParamsI.Instigator = this;

	AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), ParamsI);
	if (projectile)
	{
		projectile->Start();
		CheckNumberProjectile++;
		if (CheckNumberProjectile == NumberProjectTile)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
			CheckNumberProjectile = 0;
			return TimerFire();
		}
	}
}