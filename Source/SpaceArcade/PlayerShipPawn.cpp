#include "PlayerShipPawn.h"

APlayerShipPawn::APlayerShipPawn()
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
	HealthComponent->OnDie.AddDynamic(this, &APlayerShipPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &APlayerShipPawn::DamageTaked);

	//=========================
	// Create Spring Arm for Camera
	//=========================

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

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
	// Create Camera for Ship
	//=========================

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();

	ShootEffectOne->DeactivateSystem();
	ShootEffectTwo->DeactivateSystem();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerShipPawn::Fire, SecondTime, true, FrequencyTime); //Timer for Shoot Fire
}

void APlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

	// Function for Health Point Ship
bool APlayerShipPawn::TDamage(FDamageData DamageData)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShake, 1.0f);

	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageData.DamageValue, HealthComponent->GetHealth());
	return HealthComponent->TDamage(DamageData);
}
	
	// Function for Die Ship
void APlayerShipPawn::Die()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	Destroy();
}

	// Finction for Track DamageTaked
void APlayerShipPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

	// Finction for Shoot Ship
void APlayerShipPawn::Fire()
{
	ShootEffectOne->ActivateSystem();
	ShootEffectTwo->ActivateSystem();
	AudioEffect->Play();

	if (Type == EProjectType::FireProjectile)
	{
		if (LevelShip == 1)
		{
			AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());

			if (projectileOne)
			{
				FRotator nextRotation = GetActorRotation();
				nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
				projectileOne->AddActorWorldRotation(nextRotation);

				projectileOne->Start();
			}
		}

		if (LevelShip == 2)
		{
			FRotator RotatorProjectile = FRotator(0, 0, 0);
			for (int x = 0; x < LevelShip; ++x)
			{
				AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());

				RotatorProjectile += FRotator(0.f, 4.f, 0.f);

				if (x == 0)
				{
					projectileOne->SetActorRotation(FRotator(0.f, 0.f, 0.f) - RotatorProjectile);
				}
				if (x == 1)
				{
					projectileOne->SetActorRotation(FRotator(0.f, 0.f, 0.f) + RotatorProjectile);
				}

				if (projectileOne)
				{
					FRotator nextRotation = GetActorRotation();
					nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
					projectileOne->AddActorWorldRotation(nextRotation);

					projectileOne->Start();
				}
			}

		}
		if (LevelShip == 3)
		{
			FRotator RotatorProjectile = FRotator(0, 0, 0);
			for (int x = 0; x < LevelShip; ++x)
			{
				AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());
				
				RotatorProjectile += FRotator(0.f, 10.f, 0.f);

				projectileOne->SetActorRotation(FRotator(0.f, -20.f, 0.f) + RotatorProjectile);

				if (projectileOne)
				{
					FRotator nextRotation = GetActorRotation();
					nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
					projectileOne->AddActorWorldRotation(nextRotation);

					projectileOne->Start();
				}
			}
		}

		if (LevelShip == 1)
		{
			AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

			if (projectileTwo)
			{
				FRotator nextRotation = GetActorRotation();
				nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
				projectileTwo->AddActorWorldRotation(nextRotation);

				projectileTwo->Start();
			}
		}

		if (LevelShip == 2)
		{
			FRotator RotatorProjectile = FRotator(0, 0, 0);
			for (int x = 0; x < LevelShip; ++x)
			{
				AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

				RotatorProjectile += FRotator(0.f, 4.f, 0.f);
				
				if (x == 0)
				{
					projectileTwo->SetActorRotation(FRotator(0.f, 0.f, 0.f) - RotatorProjectile);
				}
				if (x == 1)
				{
					projectileTwo->SetActorRotation(FRotator(0.f, 0.f, 0.f) + RotatorProjectile);
				}
			
				if (projectileTwo)
				{
					FRotator nextRotation = GetActorRotation();
					nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
					projectileTwo->AddActorWorldRotation(nextRotation);

					projectileTwo->Start();
				}
			}

		}
		if (LevelShip == 3)
		{
			FRotator RotatorProjectile = FRotator(0, 0, 0);
			for (int x = 0; x < LevelShip; ++x)
			{
				AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

				RotatorProjectile += FRotator(0.f, 10.f, 0.f);

				projectileTwo->SetActorRotation(FRotator(0.f, -20.f, 0.f) + RotatorProjectile);

				if (projectileTwo)
				{
					FRotator nextRotation = GetActorRotation();
					nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
					projectileTwo->AddActorWorldRotation(nextRotation);

					projectileTwo->Start();
				}
			}
		}
	}
}

