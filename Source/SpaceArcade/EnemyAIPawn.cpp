
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

	ProjectileSpawnPointOne = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point One"));
	ProjectileSpawnPointOne->SetupAttachment(BodyMesh);
	ProjectileSpawnPointTwo = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point Two"));
	ProjectileSpawnPointTwo->SetupAttachment(BodyMesh);

	//=========================
	// Create Health Component for Ship
	//=========================

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddDynamic(this, &AEnemyAIPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &AEnemyAIPawn::DamageTaked);

	//=========================
	// Create Shoot Effect for Cannon
	//=========================

	ShootEffectOne = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect One"));
	ShootEffectOne->SetupAttachment(ProjectileSpawnPointOne);
	ShootEffectTwo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect Two"));
	ShootEffectTwo->SetupAttachment(ProjectileSpawnPointTwo);

	//=========================
	// Create Audio Effect for Cannon
	//=========================

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot audio effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPointOne);
}

void AEnemyAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 0.1f, true, 0.5f); //Timer for Shoot Fire
}

float AEnemyAIPawn::FMovementComponent()
{
	return TargetForwardAxisValue = MoveSpeed;
}

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

	FRotator CurrentRotation = GetActorRotation();
	float yawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
	yawRotation += CurrentRotation.Yaw;

	FRotator newRotation = FRotator(0.f, yawRotation, 0.f);

	SetActorRotation(newRotation);
}

void AEnemyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Function for Health Point Ship
bool AEnemyAIPawn::TDamage(FDamageData DamageData)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageData.DamageValue, HealthComponent->GetHealth());
	return HealthComponent->TDamage(DamageData);
}

// Function for Die Ship
void AEnemyAIPawn::Die()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	Destroy();
}

// Finction for Track DamageTaked
void AEnemyAIPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

// Finction for Shoot Ship
void AEnemyAIPawn::Fire()
{
	ShootEffectOne->ActivateSystem();
	ShootEffectTwo->ActivateSystem();
	AudioEffect->Play();

	if (Type == EProjectType::FireProjectile)
	{
		AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());
		if (projectileOne)
		{
			projectileOne->Start();
		}

		AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());
		if (projectileTwo)
		{
			projectileTwo->Start();
		}
	}
}