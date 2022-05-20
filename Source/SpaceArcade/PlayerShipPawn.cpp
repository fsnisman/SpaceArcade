/*
*  Библеотеки
*/

#include "PlayerShipPawn.h"

/*
*  Код
*/

// Иницилизация объекта
APlayerShipPawn::APlayerShipPawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = BodyMesh;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	ProjectileSpawnPointOne = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point One"));
	ProjectileSpawnPointOne->SetupAttachment(BodyMesh);
	ProjectileSpawnPointTwo = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point Two"));
	ProjectileSpawnPointTwo->SetupAttachment(BodyMesh);
	ProjectileSpawnPointSpecial = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point Special"));
	ProjectileSpawnPointSpecial->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddDynamic(this, &APlayerShipPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &APlayerShipPawn::DamageTaked);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	ShootEffectOne = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect One"));
	ShootEffectOne->SetupAttachment(ProjectileSpawnPointOne);
	ShootEffectTwo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect Two"));
	ShootEffectTwo->SetupAttachment(ProjectileSpawnPointTwo);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot audio effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPointOne);

	AudioEffectSpecial = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot special audio effect"));
	AudioEffectSpecial->SetupAttachment(ProjectileSpawnPointOne);

	EngineEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect"));
	EngineEffect->SetupAttachment(BodyMesh);

	EngineEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect 2"));
	EngineEffect2->SetupAttachment(BodyMesh);

	LineFlyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect"));
	LineFlyEffect->SetupAttachment(BodyMesh);

	LineFlyEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect 2"));
	LineFlyEffect2->SetupAttachment(BodyMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	AudioEffectDie = CreateDefaultSubobject<USoundBase>(TEXT("Audio Exlosion effect"));

	ExlosionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Exlosion effect"));

	AudioEffectPunch = CreateDefaultSubobject<UAudioComponent>(TEXT("Punch audio effect"));
	AudioEffectPunch->SetupAttachment(BodyMesh);
}

// Функция получение текущего здоровья игрока
float APlayerShipPawn::GetCurretHealth()
{
	return HealthComponent->GetHealth();
}

// Функция получение макисального здоровья игрока
float APlayerShipPawn::GetMaxHealth()
{
	return HealthComponent->GetHealthMax();
}

// Начало действия при создании пешки игрока
void APlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();

	// Отключить партиклы срельбы
	ShootEffectOne->DeactivateSystem();
	ShootEffectTwo->DeactivateSystem();

	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Обновление здоровья
	HealthComponent->MaxHealth *= GameInstance->UpgradeHealht;
	HealthComponent->CurrentHealth *= GameInstance->UpgradeHealht;

	if (!bActiveMenuWidget)
	{
		// Запуск камеры шейк
		GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShakeStart, 1.0f);
		// Запуск таймера стрельбы
		GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerShipPawn::Fire, 1, true, FireTimer);
	}
	else 
	{
		// Открепить рычаг от пешки игрока
		SpringArm->DetachExternalPackage();
	}
}

// Обновление объекты в каждом тике
void APlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Каст на данные игрока
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(this->GetPlayerState());

	// Проверка на создание
	if (playerState)
	{
		// Перезапись уровня корабля
		LevelShip = playerState->LevelShip;
		// Презаписть текущего значения здоровья
		playerState->PlayerHP = HealthComponent->CurrentHealth;
	}
}

// Установка компонента ввода игрока
void APlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Получение урона
bool APlayerShipPawn::TDamage(FDamageData DamageData)
{
	// Запуск камеры шейк
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShake, 1.0f);
	// Перезапись переменной для виньетки
	TriggerVingget = true;
	// Запуск эффекта удара
	AudioEffectPunch->Play();

	// Тег для отображения здоровья
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageData.DamageValue, HealthComponent->GetHealth());
	// Вернуть значение полученного урона
	return HealthComponent->TDamage(DamageData);
}
	
// Смерть игрока
void APlayerShipPawn::Die()
{
	// Перезапись переменной смерти
	DiedShip = true;

	// Открепить рычак от корабля игрока
	SpringArm->DetachExternalPackage();

	// Переменна параметры справна
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	
	// Диактивет компоненты пешки
	BodyMesh->DestroyComponent(false);
	HitCollider->DestroyComponent(false);
	ProjectileSpawnPointOne->Deactivate();
	ProjectileSpawnPointTwo->Deactivate();
	ShootEffectOne->DeactivateSystem();
	ShootEffectTwo->DeactivateSystem();
	EngineEffect->DeactivateSystem();
	EngineEffect2->DeactivateSystem();

	// Запуск эффектов взрыва
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExlosionEffect, GetActorTransform());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectDie, GetActorLocation());

	// Замедление времени
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.3);

	// Повернуть рычак на -90 по X
	SpringArm->SetRelativeRotation(FRotator(-90, 0, 0));
}

// Функция отображение здоровья в логах
void APlayerShipPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

// Функция стрельбы
void APlayerShipPawn::Fire()
{
	// Проверка на смерть игрока
	if (DiedShip == false)
	{
		// Запуск эффектов стрельбы
		ShootEffectOne->ActivateSystem();
		ShootEffectTwo->ActivateSystem();
		AudioEffect->Play();

		// Проверка на этот класс
		if (this)
		{
			// Проверка на тип снаряда
			if (Type == EProjectType::FireProjectile)
			{
				// Проверка на напрления стрельбы
				if (ProjectileSpawnPointOne)
				{
					// Проверка на уровнь корабля
					if (LevelShip == 1)
					{
						// Спавн снаряда
						AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());

						// Проверка на снаряд
						if (projectileOne)
						{
							// Повернуть снаряд
							FRotator nextRotation = GetActorRotation();
							// Рандомно прибавлять поворот
							nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
							// Добавить значение в снаряд
							projectileOne->AddActorWorldRotation(nextRotation);

							// Запуск снаряда
							projectileOne->Start();
						}
					}
					// Проверка на уровнь корабля
					if (LevelShip == 2)
					{
						// Переменна для поворота направления
						FRotator RotatorProjectile = FRotator(0, 0, 0);
						// Цикл на создание нескольких снарядов в разных направлениях
						for (int x = 0; x < LevelShip; ++x)
						{
							// Спавн снаряда
							AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());
							// Проверка на снаряд
							if (x == 0 && projectileOne)
							{
								// Повернуть направление снаряда
								RotatorProjectile += FRotator(0.f, 4.f, 0.f);
								projectileOne->SetActorRotation(FRotator(0.f, 0.f, 0.f) - RotatorProjectile);
							}
							// Проверка на снаряд
							if (x == 1 && projectileOne)
							{
								// Повернуть направление снаряда
								RotatorProjectile += FRotator(0.f, 4.f, 0.f);
								projectileOne->SetActorRotation(FRotator(0.f, 0.f, 0.f) + RotatorProjectile);
							}
							// Проверка на снаряд
							if (projectileOne)
							{
								// Повернуть снаряд
								FRotator nextRotation = GetActorRotation();
								// Рандомно прибавлять поворот
								nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
								// Добавить значение в снаряд
								projectileOne->AddActorWorldRotation(nextRotation);

								// Запуск снаряда
								projectileOne->Start();
							}
						}

					}
					// Проверка на уровнь корабля
					if (LevelShip == 3)
					{
						// Переменна для поворота направления
						FRotator RotatorProjectile = FRotator(0, 0, 0);
						// Цикл на создание нескольких снарядов в разных направлениях
						for (int x = 0; x < LevelShip; ++x)
						{
							// Спавн снаряда
							AProjectTile* projectileOne = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointOne->GetComponentLocation(), ProjectileSpawnPointOne->GetComponentRotation());

							// Проверка на снаряд
							if (projectileOne)
							{
								// Переменна направления
								RotatorProjectile += FRotator(0.f, 10.f, 0.f);

								// Установить поворт снаряда
								projectileOne->SetActorRotation(FRotator(0.f, -20.f, 0.f) + RotatorProjectile);

								// Повернуть снаряд
								FRotator nextRotation = GetActorRotation();
								// Рандомно прибавлять поворот
								nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
								// Добавить значение в снаряд
								projectileOne->AddActorWorldRotation(nextRotation);

								// Запуск снаряда
								projectileOne->Start();
							}
						}
					}
				}
				// Проверка на напрления стрельбы
				if (ProjectileSpawnPointTwo)
				{
					// Проверка на уровнь корабля
					if (LevelShip == 1)
					{
						// Спавн снаряда
						AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

						// Проверка на снаряд
						if (projectileTwo)
						{
							// Повернуть снаряд
							FRotator nextRotation = GetActorRotation();
							// Рандомно прибавлять поворот
							nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
							// Добавить значение в снаряд
							projectileTwo->AddActorWorldRotation(nextRotation);

							// Запуск снаряда
							projectileTwo->Start();
						}
					}
					// Проверка на уровнь корабля
					if (LevelShip == 2)
					{
						// Переменна для поворота направления
						FRotator RotatorProjectile = FRotator(0, 0, 0);
						// Цикл на создание нескольких снарядов в разных направлениях
						for (int x = 0; x < LevelShip; ++x)
						{
							// Спавн снаряда
							AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

							// Проверка на снаряд
							if (x == 0 && projectileTwo)
							{
								// Повернуть направление снаряда
								RotatorProjectile += FRotator(0.f, 4.f, 0.f);
								projectileTwo->SetActorRotation(FRotator(0.f, 0.f, 0.f) - RotatorProjectile);
							}
							// Проверка на снаряд
							if (x == 1 && projectileTwo)
							{
								// Повернуть направление снаряда
								RotatorProjectile += FRotator(0.f, 4.f, 0.f);
								projectileTwo->SetActorRotation(FRotator(0.f, 0.f, 0.f) + RotatorProjectile);
							}

							// Проверка на снаряд
							if (projectileTwo)
							{
								// Повернуть снаряд
								FRotator nextRotation = GetActorRotation();
								// Рандомно прибавлять поворот
								nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
								// Добавить значение в снаряд
								projectileTwo->AddActorWorldRotation(nextRotation);

								// Запуск снаряда
								projectileTwo->Start();
							}
						}

					}
					// Проверка на уровнь корабля
					if (LevelShip == 3)
					{
						// Переменна для поворота направления
						FRotator RotatorProjectile = FRotator(0, 0, 0);
						// Цикл на создание нескольких снарядов в разных направления
						for (int x = 0; x < LevelShip; ++x)
						{
							// Спавн снаряда
							AProjectTile* projectileTwo = GetWorld()->SpawnActor<AProjectTile>(ProjectileClass, ProjectileSpawnPointTwo->GetComponentLocation(), ProjectileSpawnPointTwo->GetComponentRotation());

							// Проверка на снаряд
							if (projectileTwo)
							{
								// Переменна направления
								RotatorProjectile += FRotator(0.f, 10.f, 0.f);

								// Установить поворт снаряда
								projectileTwo->SetActorRotation(FRotator(0.f, -20.f, 0.f) + RotatorProjectile);

								// Повернуть снаряд
								FRotator nextRotation = GetActorRotation();
								// Рандомно прибавлять поворот
								nextRotation.Yaw = nextRotation.Yaw + FMath::RandRange(-1, 1);
								// Добавить значение в снаряд
								projectileTwo->AddActorWorldRotation(nextRotation);

								// Запуск снаряда
								projectileTwo->Start();
							}
						}
					}
				}
			}
		}
	}
	// Проверка на пройденный уровнь
	if (LevelComplitet)
	{
		// Диактивейт эффект стрельбы
		ShootEffectOne->DeactivateSystem();
		ShootEffectTwo->DeactivateSystem();
		// Онулировать сглаживания полета
		FrequencyTime = 0;
		// Онулировать частоты стрельбы
		SecondTime = 0;
		// Открепить рычаг от пешки игрока
		SpringArm->DetachExternalPackage();
		// Очистка таймера
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	}

	// Запуск таймера стрельбы
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerShipPawn::Fire, SecondTime, true, FrequencyTime);
}

// Функция особой стрельбы
void APlayerShipPawn::FireSpecial()
{
	// Запуск звука стрельбы
	AudioEffectSpecial->Play();

	// Цикл на создание снаряда по наличию тега "ProjectileSpawnPointSpecial"
	for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPointSpecial")))
	{
		// Справн снаряда
		AProjectTile* projectile = GetWorld()->SpawnActor<AProjectTile>(ProjectileClassSpecial, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation());

		// Проверка на снаряд
		if (projectile)
		{
			// Проиграть звук стрельбы
			AudioEffect->Play();
			// Запуск снаряда
			projectile->Start();
		}
	}
}

// Функция готовности стрельбы
void APlayerShipPawn::OnRedyOfFire()
{
	// Диактивейт эффектр стрельбы
	ShootEffectOne->DeactivateSystem();
	ShootEffectTwo->DeactivateSystem();

	// Запуск таймера стрельбы
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerShipPawn::Fire, 1, true, 4);
}

