
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
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

	HitCollider2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider 2"));
	HitCollider2->SetupAttachment(BodyMesh);
	HitCollider2->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

	HitCollider3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider 3"));
	HitCollider3->SetupAttachment(BodyMesh);
	HitCollider3->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

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

	SpecialShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting special effect"));
	SpecialShootEffect->SetupAttachment(ProjectileSpawnPoint);


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
	// Create Audio Effect for Exlosion
	//=========================

	AudioEffectDie = CreateDefaultSubobject<USoundBase>(TEXT("Audio Exlosion effect"));

	//=========================
	// Create Audio Effect for Cannon
	//=========================

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot audio effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPoint);
}

void AEnemyAIPawn::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorEnableCollision(false);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::EnableCollision, 1, true, 2);

	SpecialShootEffect->DeactivateSystem();
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

	/*AEnemyAIPawn* Boss = this;
	if (Boss->ActorHasTag(TEXT("Boss")) && TargetForwardAxisValue == 0)
	{

		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("Boss move")));
		FVector NewLocation = GetActorLocation();

		if (NewLocation.X > 300)
		{
			Direction = Direction * -1;
		}

		if (NewLocation.X < -300)
		{
			Direction = Direction * -1;
		}

		NewLocation.X += Direction * 0.4f;

		SetActorLocation(NewLocation);
	}*/

	if(!tbBackMoveShip)
	{
		FVector MovePosition = CurrentLocation + ForwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
		SetActorLocation(MovePosition, true);
	}
	else
	{
		FVector MovePosition = CurrentLocation + ForwardVector * -MoveSpeed * TargetForwardAxisValue * DeltaTime;
		SetActorLocation(MovePosition, true);
	}

	if (bTrackingPlayerArrow)
	{
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerShip)
		{
			for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileRotate")))
			{
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerShip->GetActorLocation());
				FRotator CurreRotation = Cast<UArrowComponent>(Comp)->GetComponentRotation();
				TargetRotation.Pitch = CurreRotation.Pitch;
				TargetRotation.Roll = CurreRotation.Roll;
				Cast<UArrowComponent>(Comp)->SetWorldRotation(FMath::RInterpConstantTo(CurreRotation, TargetRotation, DeltaTime, MovementAccurancy));
			}
		}
	}

	if (bProjectileRotate360)
	{
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerShip)
		{
			for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileRotate360")))
			{
				Cast<UArrowComponent>(Comp)->AddRelativeRotation(FRotator(0,1,0));
			}
		}
	}

	if (bTrackingPlayerShip)
	{
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (PlayerShip)
		{
			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerShip->GetActorLocation());
			FRotator CurreRotation = BodyMesh->GetRelativeRotation();
			TargetRotation.Pitch = CurreRotation.Pitch;
			TargetRotation.Roll = CurreRotation.Roll;
			BodyMesh->SetWorldRotation(FMath::RInterpConstantTo(CurreRotation, TargetRotation, DeltaTime, MovementAccurancy));
		}
	}

	if (tbRotateShip)
	{
		FRotator CurrentRotation = GetActorRotation();
		float yawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
		yawRotation += CurrentRotation.Yaw;

		FRotator newRotation = FRotator(0.f, yawRotation, 0.f);

		SetActorRotation(newRotation);
	}
}

void AEnemyAIPawn::RotateArrowTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator currRotation = ProjectileSpawnPoint->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	ProjectileSpawnPoint->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, MovementAccurancy));
}

void AEnemyAIPawn::EnableCollision()
{
	this->SetActorEnableCollision(true);
	GetWorldTimerManager().ClearTimer(TimerHandle);
	TimerFire();
}

FVector AEnemyAIPawn::GetEyesPosition()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

TArray<FVector> AEnemyAIPawn::GetPatrollingPoints()
{
	TArray<FVector> points;

	for (ATargetPoint* point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}

	return points;
}

void AEnemyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Function for Health Point Enemy Ship
bool AEnemyAIPawn::TDamage(FDamageData DamageData)
{
	return HealthComponent->TDamage(DamageData);
}

// Function Collision 
void AEnemyAIPawn::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != playerShip)
	{
		return;
	}

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = ExplosionDamage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			damageTakerActor->TDamage(damageData);
			damageData.DamageValue = ExplosionDamageEnemy;
			TDamage(damageData);
		}
		else
		{
			if (HealthComponent->CurrentHealth == 0)
			{
				Die();
			}
		}
	}
}


// Function for Die Enemy Ship
void AEnemyAIPawn::Die()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExlosionEffect, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectDie, GetActorLocation());

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

	if (bFireToPlayer)
	{
		if (bScatterProjectTile)
		{
			FRotator RotatorProjectile;
			for (int x = 0; x < ScatterProjectTile; ++x)
			{
				AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation(), ParamsI);

				RotatorProjectile = RotatorProjectile + FRotator(0.f, 20.f, 0.f);

				projectile->SetActorRotation(FRotator(0.f, 140.f, 0.f) + RotatorProjectile);

				if (projectile)
				{
					projectile->Start();
				}
			}

			CheckNumberProjectile++;
			if (CheckNumberProjectile == CountProjectTile)
			{
				GetWorldTimerManager().ClearTimer(TimerHandle);
			}
		}
		else
		{
			CheckNumberProjectile++;
			if (CheckNumberProjectile == CountProjectTile)
			{
				AEnemyAIPawn* Boss = this;

				if(Boss->ActorHasTag(TEXT("Boss")))
				{
					int Fire = 0;
					CheckNumberProjectile = 0;

					Fire = FMath::RandRange(0, 2);

					if (Fire == 0)
					{
						GEngine->AddOnScreenDebugMessage(5, 2, FColor::Red, FString::Printf(TEXT("Shoot")));
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::FireBoss, FireRange, true, FireFrequency);
					}
					
					if (Fire == 1)
					{
						GEngine->AddOnScreenDebugMessage(6, 3, FColor::Red, FString::Printf(TEXT("Shoot360")));
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire360, FireRange, true, 3);
					}

					if (Fire == 2)
					{
						GEngine->AddOnScreenDebugMessage(7, 4, FColor::Red, FString::Printf(TEXT("ShootSpecial")));
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::FireSpecial, 1, true, 10);
						SpecialShootEffect->ActivateSystem();
					}
				}
				else
				{
					for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileSpawnPoint")))
					{
						AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

						if (projectile)
						{
							projectile->Start();
						}
					}

					GetWorldTimerManager().ClearTimer(TimerHandle);
				}
			}
		}
	}
}

void AEnemyAIPawn::FireSpecial()
{
	SpecialShootEffect->DeactivateSystem();
	AudioEffect->Play();

	FActorSpawnParameters ParamsI;
	ParamsI.Instigator = this;

	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (bFireToPlayer)
	{
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPointSpecial")))
		{
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClassSpecial, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			if (projectile)
			{
				const FAttachmentTransformRules AttachActor(EAttachmentRule::KeepWorld, true);

				projectile->AttachToActor(this, AttachActor, NAME_None);
				projectile->Start();
			}
		}

		CountProjectTile = 1;

		CheckNumberProjectile++;
		if (CheckNumberProjectile == CountProjectTile)
		{
			CheckNumberProjectile = 0;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}
		
	}
}

void AEnemyAIPawn::Fire360()
{
	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	FActorSpawnParameters ParamsI;
	ParamsI.Instigator = this;

	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (bFireToPlayer)
	{
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPoint360")))
		{
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass2, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			if (projectile)
			{
				const FAttachmentTransformRules AttachActor(EAttachmentRule::KeepWorld, true);

				projectile->AttachToActor(this, AttachActor, NAME_None);
				projectile->Start();
			}
		}

		CheckNumberProjectile++;
		if (CheckNumberProjectile == 30)
		{
			CheckNumberProjectile = 0;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}

	}
}

void AEnemyAIPawn::FireBoss()
{
	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	FActorSpawnParameters ParamsI;
	ParamsI.Instigator = this;

	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (bFireToPlayer)
	{
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPoint")))
		{
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			if (projectile)
			{
				projectile->Start();
			}
		}

		CheckNumberProjectile++;
		if (CheckNumberProjectile == 10)
		{
			CheckNumberProjectile = 0;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}

	}
}

void AEnemyAIPawn::SetPatrollingPoints(const TArray<ATargetPoint*>& NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}