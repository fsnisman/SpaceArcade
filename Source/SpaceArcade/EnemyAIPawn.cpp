/*
*  Библеотеки
*/

#include "EnemyAIPawn.h"
#include "WidgetEnemyHP.h"

/*
*  Код
*/

// Иницилизация объекта
AEnemyAIPawn::AEnemyAIPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = BodyMesh;

	MaterialOne = CreateDefaultSubobject<UMaterialInterface>("MaterialOne");
	MaterialTwo = CreateDefaultSubobject<UMaterialInterface>("MaterialTwo");
	MaterialThree = CreateDefaultSubobject<UMaterialInterface>("MaterialThree");

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

	HitCollider2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider 2"));
	HitCollider2->SetupAttachment(BodyMesh);
	HitCollider2->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

	HitCollider3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider 3"));
	HitCollider3->SetupAttachment(BodyMesh);
	HitCollider3->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAIPawn::OnMeshOverlapBegin);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddDynamic(this, &AEnemyAIPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &AEnemyAIPawn::DamageTaked);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting effect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	SpecialShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shooting special effect"));
	SpecialShootEffect->SetupAttachment(ProjectileSpawnPoint);

	EngineEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect"));
	EngineEffect->SetupAttachment(BodyMesh);

	EngineEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Engine Fire effect 2"));
	EngineEffect2->SetupAttachment(BodyMesh);

	LineFlyEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect"));
	LineFlyEffect->SetupAttachment(BodyMesh);

	LineFlyEffect2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Line Fly effect 2"));
	LineFlyEffect2->SetupAttachment(BodyMesh);

	ExlosionEffectDie = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Exlosion effect Die"));
	ExlosionEffectDie->SetupAttachment(BodyMesh);

	FireExlosionEffectDie = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fir Exlosion effect Die"));
	FireExlosionEffectDie->SetupAttachment(BodyMesh);

	ExlosionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Exlosion effect"));

	AudioEffectDie = CreateDefaultSubobject<USoundBase>(TEXT("Audio Exlosion effect"));

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Shoot audio effect"));
	AudioEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffectPunch = CreateDefaultSubobject<UAudioComponent>(TEXT("Punch audio effect"));
	AudioEffectPunch->SetupAttachment(BodyMesh);

	BarHP = CreateDefaultSubobject<UWidgetComponent>("BarHP");
	BarHP->SetupAttachment(BodyMesh);
}

// Начало действия при создании пешки игрока
void AEnemyAIPawn::BeginPlay()
{
	Super::BeginPlay();

	// Отключение коллизии
	this->SetActorEnableCollision(false);

	// Проверка на объект
	if (this)
	{
		// Каст на виджет 
		UWidgetEnemyHP* HealthBar = Cast<UWidgetEnemyHP>(BarHP->GetUserWidgetObject());
		// Привязать виджет к объекту
		HealthBar->SetOwner(this);
	}

	// Перезаписть время стрельбы
	fTimerFire = FfTimerFire;
	// Запуск таймера стрельбы
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::EnableCollision, 1, true, fTimerFire);
	
	// Перезапись переменных 
	DropItem = dDropItem;
	bTrackingPlayerArrow = tbRotateArrow;
	MoveSpeed = fMoveSpeed;
	RotationSpeed = FRotationSpeed;
	MovementAccurancy = FMovementAccurancy;
	ForwardSmootheness = FForwardSmootheness;
	RotationSmootheness = FRotationSmootheness;
	CountProjectTile = iCountProjectTile;

	// Проверка на смену материала
	if (tbSetMaterial)
	{
		// Изменить материал
		BodyMesh->SetMaterial(0, MaterialTwo);
	}

	// Отключить партиклы стрельбы
	SpecialShootEffect->DeactivateSystem();
	// Отключить партикл взрыва смерти
	ExlosionEffectDie->DeactivateSystem();

	// Цикл на наличе тега "Fire"
	for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("Fire")))
	{
		// Отключить партикл
		Cast<UParticleSystemComponent>(Comp)->DeactivateSystem();
	}

	// Активировать партиклы
	EngineEffect->ActivateSystem();
	EngineEffect2->ActivateSystem();
	LineFlyEffect->ActivateSystem();
	LineFlyEffect2->ActivateSystem();
}

// Время стрельбы
void AEnemyAIPawn::TimerFire()
{
	// Запуск таймера стрельбы
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, FireRange, true, FireFrequency);
}

// Остановить движение
void AEnemyAIPawn::StopMove()
{
	// Запить этотго объекта
	AEnemyAIPawn* Ship = this;
	// Остановить движение
	FMovementComponent(0.f);
	// Изименить значение перемнной
	bTrackingPlayerShip = tbRotateShipToPlayer;
}

// Функция получени направление движения
FVector AEnemyAIPawn::GetArrowForwardVector()
{
	return ProjectileSpawnPoint->GetForwardVector();
}

// Функция привязки значение движение
float AEnemyAIPawn::FMovementComponent(float ValueAxis)
{
	// Проверка на нулевое движение
	if (ValueAxis == 0)
	{
		return TargetForwardAxisValue = ValueAxis;
	}
	else
	{
		return TargetForwardAxisValue = MoveSpeed;
	}

}

// Функция привязки Значение поворота
float AEnemyAIPawn::FRotationComponent(float ValueAxis)
{
	return TargetRightAxisValue = ValueAxis;
}

// Обновление объекта на каждый тик
void AEnemyAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Интерполяция текущего значение движения
	CurrentForwardAxisValue = FMath::FInterpTo(CurrentForwardAxisValue, TargetForwardAxisValue, DeltaTime, ForwardSmootheness);
	// Присвоить направление движения
	TargetForwardAxisValue = CurrentForwardAxisValue;

	// Текущие место расположение
	FVector CurrentLocation = GetActorLocation();
	// Текущее направление
	FVector ForwardVector = GetActorForwardVector();

	// Проверка на движение назад
	if(!tbBackMoveShip)
	{
		// Векторая переменна направление движение
		FVector MovePosition = CurrentLocation + ForwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
		// Установить значение переменной
		SetActorLocation(MovePosition, true);
	}
	else
	{	// Обратная векторая переменна направление движение
		FVector MovePosition = CurrentLocation + ForwardVector * -MoveSpeed * TargetForwardAxisValue * DeltaTime;
		// Установить значение переменной
		SetActorLocation(MovePosition, true);
	}

	// Проверка на слежку направление стрельбы
	if (bTrackingPlayerArrow)
	{
		//Каст на игрока
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		// Проверка на игрока
		if (PlayerShip)
		{
			// Цикл на наличие тега "ProjectileRotate"
			for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileRotate")))
			{
				// Значение поворота
				FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerShip->GetActorLocation());
				// Значение текущего поворота
				FRotator CurreRotation = Cast<UArrowComponent>(Comp)->GetComponentRotation();
				// Присвоить значения X
				TargetRotation.Pitch = CurreRotation.Pitch;
				// Присвоить значение Y
				TargetRotation.Roll = CurreRotation.Roll;
				// Каст направление на поворт
				Cast<UArrowComponent>(Comp)->SetWorldRotation(FMath::RInterpConstantTo(CurreRotation, TargetRotation, DeltaTime, MovementAccurancy));
			}
		}
	}

	// Проверка поворт направление на 360 градусов
	if (bProjectileRotate360)
	{
		// Каст на игрока
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		// Проверка на игрока
		if (PlayerShip)
		{
			// Цикл на наличие тега "ProjectileRotate360"
			for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileRotate360")))
			{
				//Каст на постоянно прибавление поворота
				Cast<UArrowComponent>(Comp)->AddRelativeRotation(FRotator(0,1,0));
			}
		}
	}

	// Проверка на слежку за игроком
	if (bTrackingPlayerShip)
	{
		// Каст на игрока
		APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		// Проверка на игрока
		if (PlayerShip)
		{
			// Значение поворота
			FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerShip->GetActorLocation());
			// Значение текущего поворота
			FRotator CurreRotation = BodyMesh->GetRelativeRotation();
			// Присвоить значения X
			TargetRotation.Pitch = CurreRotation.Pitch;
			// Присвоить значение Y
			TargetRotation.Roll = CurreRotation.Roll;
			// Каст направление на поворт
			BodyMesh->SetWorldRotation(FMath::RInterpConstantTo(CurreRotation, TargetRotation, DeltaTime, MovementAccurancy));
		}
	}

	// Проверка на поворт корабля
	if (tbRotateShip)
	{
		// Текущие значение поворота
		FRotator CurrentRotation = GetActorRotation();
		// Поворот по Z
		float yawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
		// Прибавление поворота по Z
		yawRotation += CurrentRotation.Yaw;

		// Новый поворт
		FRotator newRotation = FRotator(0.f, yawRotation, 0.f);

		// Установка поворота
		SetActorRotation(newRotation);
	}
}

// Функция повопрота напрвелния движения
void AEnemyAIPawn::RotateArrowTo(FVector TargetPosition)
{
	// Значение поворота
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	// Текущие значение поворота
	FRotator currRotation = ProjectileSpawnPoint->GetComponentRotation();
	// Повернуть на X
	targetRotation.Pitch = currRotation.Pitch;
	// Повернуть на Y
	targetRotation.Roll = currRotation.Roll;
	// Повернуть направление
	ProjectileSpawnPoint->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, MovementAccurancy));
}

// Получение текущего здоровья
float AEnemyAIPawn::GetCurretHealth()
{
	return HealthComponent->GetHealth();
}

// Получени максимального здоровья
float AEnemyAIPawn::GetMaxHealth()
{
	return HealthComponent->GetHealthMax();
}

// Включение коллизии
void AEnemyAIPawn::EnableCollision()
{
	//Включить коллизию
	this->SetActorEnableCollision(true);
	// Очистить таймер
	GetWorldTimerManager().ClearTimer(TimerHandle);
	// Запустить таймер стрельбы
	TimerFire();
}

// Получени координат напавления стрельбы
FVector AEnemyAIPawn::GetEyesPosition()
{
	return ProjectileSpawnPoint->GetComponentLocation();
}

// Получение всех точек патруля
TArray<FVector> AEnemyAIPawn::GetPatrollingPoints()
{
	// Массив точек
	TArray<FVector> points;

	// Цикл на добавление месторасполежнии точек
	for (ATargetPoint* point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}

	return points;
}

// Установка компонента ввода врага
void AEnemyAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Получение урона
bool AEnemyAIPawn::TDamage(FDamageData DamageData)
{
	AudioEffectPunch->Play();
	return HealthComponent->TDamage(DamageData);
}

// Фукнция пересечения объекта с другими объектами
void AEnemyAIPawn::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Переменная владельца
	AActor* owner = GetOwner();
	// Переменна владеющего владельца
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	// Проверка на игрока
	if (OtherActor != playerShip)
	{
		return;
	}

	// Проверка других объектов на владельцов
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		// Каст на передачу урона
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		// Проверка на создание объекта
		if (damageTakerActor)
		{
			// Создание переменно уроная
			FDamageData damageData;
			// Запись урона в переменную
			damageData.DamageValue = ExplosionDamage;
			// Проверка на владельца
			damageData.Instigator = owner;
			// От кого урон
			damageData.DamageMaker = this;

			// Получение урона
			damageTakerActor->TDamage(damageData);
			// Запись урона в переменную
			damageData.DamageValue = ExplosionDamageEnemy;
			// Получение урона
			TDamage(damageData);
		}             
		else
		{
			// Проверка на текущие здоровье
			if (HealthComponent->CurrentHealth == 0)
			{
				// Уничтожение объекта
				Die();
			}
		}
	}
}


// Функция уничтожение объекта
void AEnemyAIPawn::Die()
{
	// Создание босса
	AEnemyAIPawn* Boss = this;
	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	// Проверка на игрока
	if (playerShip)
	{
		// Каст на данные игрока
		ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

		// Проверка на наличе тега "Boss"
		if (!Boss->ActorHasTag(TEXT("Boss")))
		{
			// Пибавить значение уничтоженных врагов
			playerShip->CountDiedEnemyPawn++;
			// Прибавить значение очков
			playerState->iScore += FMath::RandRange(ScoreDeathMin, ScoreDeathMax);
			// Прибавить значение уничтоженных врагов
			playerState->EnemyCount++;
			// Запуск камерый шейк
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShake, 1.0f);
			// Дроп предметов
			ADropItems* Drop = GetWorld()->SpawnActor<ADropItems>(DropItem, GetActorLocation(), GetActorRotation());

			// Запуск эффекта взрыва
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExlosionEffect, GetActorTransform());
			// Запукс звука взрыва
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectDie, GetActorLocation());

			// Параметры спавна
			FActorSpawnParameters SpawnParams;
			SpawnParams.bNoFail = true;

			// Уничтожить
			Destroy();
		}
		else
		{
			// Запуск камеры шейк
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CamShake, 1.0f);

			// Прибавить значение очков
			playerState->iScore += FMath::RandRange(ScoreDeathMin, ScoreDeathMax);
			// Прибавить значение уничтоженных врагов
			playerState->EnemyCount++;

			// Активировать систему взрыва
			ExlosionEffectDie->ActivateSystem();

			// Цикл на наличие тега "Fire"
			for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("Fire")))
			{
				//Активировать систему партиклов
				Cast<UParticleSystemComponent>(Comp)->ActivateSystem();
			}
			
			// Записть на "Уровень пройден"
			playerShip->LevelComplitet = true;
			// Очистить таймер
			GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}
}

// Функция получение лога от урона
void AEnemyAIPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Ship %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}

// Функция стрельбы 
void AEnemyAIPawn::Fire()
{
	// Активировать систему выстрела
	ShootEffect->ActivateSystem();

	// Переменная босса
	AEnemyAIPawn* Boss = this;
	// Параметры спавна
	FActorSpawnParameters ParamsI;
	// Инстигатор
	ParamsI.Instigator = this;

	// Стрельба по игроку
	if (bFireToPlayer)
	{
		// Разрбос направление стрельбы
		if (bScatterProjectTile)
		{
			// Цикл на проверку наличия тега "ProjectileSpawnPointScatter"
			for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPointScatter")))
			{
				// Создать снаряд
				AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

				// Проверка на создание
				if (projectile)
				{
					// Запустить звук выстрела
					AudioEffect->Play();
					// Запустить снаряд
					projectile->Start();
				}
			}

			// Инктременитровать значение выпущенных снарядов
			CheckNumberProjectile++;
			// Проверка на выщуенных снарядов
			if (CheckNumberProjectile == CountProjectTile)
			{
				// Очитка таймера
				GetWorldTimerManager().ClearTimer(TimerHandle);
			}
		}
		else
		{
			// Проверка на наличе тега "Boss"
			if(Boss->ActorHasTag(TEXT("Boss")))
				{
					// Выбор стрельбы
					int Fire = 0;
					// Количество выпущенных снарядов
					CheckNumberProjectile = 0;

					// Рандом
					Fire = FMath::RandRange(0, 2);

					// Проверка на значение стрельбы
					if (Fire == 0)
					{
						//x GEngine->AddOnScreenDebugMessage(5, 2, FColor::Red, FString::Printf(TEXT("Shoot")));
						// Запустить таймер стрельбы 
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::FireBoss, FireRange, true, FireFrequency);
					}
					// Проверка на значение стрельбы
					if (Fire == 1)
					{
						//x GEngine->AddOnScreenDebugMessage(6, 3, FColor::Red, FString::Printf(TEXT("Shoot360")));
						// Запустить таймер стрельбы 360
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire360, FireRange, true, 2);
					}
					// Проверка на значение стрельбы
					if (Fire == 2)
					{
						//x GEngine->AddOnScreenDebugMessage(7, 4, FColor::Red, FString::Printf(TEXT("ShootSpecial")));
						// Запустить таймер особой стрельбы
						GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::FireSpecial, 1, true, 5);
						// Активитровать особый партикал
						SpecialShootEffect->ActivateSystem();
					}
				}
			else
			{
				// Цикл на проверку наличия "ProjectileSpawnPoint"
				for (UActorComponent* Comp : GetComponentsByTag(UArrowComponent::StaticClass(), TEXT("ProjectileSpawnPoint")))
				{
					// Спавн снаряда
					AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

					// Проверка на снаряд
					if (projectile)
					{
						// Запуск звука стрельбы
						AudioEffect->Play();
						// Запуск снаряда
						projectile->Start();
					}
				}

				// Инктременитровать значение выпущенных снарядов
				CheckNumberProjectile++;
				// Проверка на выщуенных снарядов
				if (CheckNumberProjectile == CountProjectTile)
				{
					// Очитка таймера
					GetWorldTimerManager().ClearTimer(TimerHandle);
				}
			}
		}
	}
}

// Функция особой стрельбы
void AEnemyAIPawn::FireSpecial()
{
	// Диактивировать партикал особой стрельбы
	SpecialShootEffect->DeactivateSystem();

	// Параметры спавна
	FActorSpawnParameters ParamsI;
	// Инстигатор
	ParamsI.Instigator = this;

	// Каст на игрока
	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Стрельба по игроку
	if (bFireToPlayer)
	{
		// Цикл на проверку наличия тега "ProjectileSpawnPointSpecial"
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPointSpecial")))
		{
			// Спавн снаряда
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClassSpecial, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			// Проврка на снаряд
			if (projectile)
			{
				// Переменная для закрепа
				const FAttachmentTransformRules AttachActor(EAttachmentRule::KeepWorld, true);

				// Запуск звука стрельбы
				AudioEffect->Play();
				// Закрепить за объектом
				projectile->AttachToActor(this, AttachActor, NAME_None);
				// Запуск снаряда
				projectile->Start();
			}
		}

		// Количество выпскаемого снаряда
		CountProjectTile = 1;

		// Инкрементация количества снарядов
		CheckNumberProjectile++;
		// Проверка сколько снарядов выпустилось
		if (CheckNumberProjectile == CountProjectTile)
		{
			// Обнуление количество снарядов
			CheckNumberProjectile = 0;
			// Запуск таймера стрельбы
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}
		
	}
}

// Функция стрельыб 360
void AEnemyAIPawn::Fire360()
{
	// Активация эффекта выстрела
	ShootEffect->ActivateSystem();

	// Параметры спавна
	FActorSpawnParameters ParamsI;
	// Интигатор
	ParamsI.Instigator = this;

	// Каст на игрока
	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Стрельба по игроку
	if (bFireToPlayer)
	{
		// Цикл на првоерку наличия тега "ProjectileSpawnPoint360"
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPoint360")))
		{
			// Спавн снаряда
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass2, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			// Проверка на снаряд
			if (projectile)
			{
				// Переменная для закрепа
				const FAttachmentTransformRules AttachActor(EAttachmentRule::KeepWorld, true);

				// Запуск звука стрельбы
				AudioEffect->Play();
				// Закрепить за объектом
				projectile->AttachToActor(this, AttachActor, NAME_None);
				// Запуск снаряда
				projectile->Start();
			}
		}

		// Инкрементация количества снарядов
		CheckNumberProjectile++;
		// Проверка сколько снарядов выпустилось
		if (CheckNumberProjectile == 20)
		{
			// Обнуление количество снарядов
			CheckNumberProjectile = 0;
			// Запуск таймера стрельбы
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}

	}
}

// Функция стрельыб босса
void AEnemyAIPawn::FireBoss()
{
	// Активировать эффект стрельбы
	ShootEffect->ActivateSystem();

	// Параметры спавна
	FActorSpawnParameters ParamsI;
	// Инстиатор
	ParamsI.Instigator = this;

	// Каст на игрока
	APlayerShipPawn* PlayerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

	// Стрельба по игроку
	if (bFireToPlayer)
	{
		// Цикл на проверку наличе тега "ProjectileSpawnPoint"
		for (UActorComponent* Comp : GetComponentsByTag(UActorComponent::StaticClass(), TEXT("ProjectileSpawnPoint")))
		{
			// Спавн снаряда
			AProjectTileEnemy* projectile = GetWorld()->SpawnActor<AProjectTileEnemy>(ProjectileClass, Cast<UArrowComponent>(Comp)->GetComponentLocation(), Cast<UArrowComponent>(Comp)->GetComponentRotation(), ParamsI);

			// Проверка на снаряд
			if (projectile)
			{
				// Запуск звука стрельбы
				AudioEffect->Play();
				// Запуск снаряда
				projectile->Start();
			}
		}

		// Инкрементация количества снарядов
		CheckNumberProjectile++;
		// Проверка сколько снарядов выпустилось
		if (CheckNumberProjectile == 10)
		{
			// Обнуление количество снарядов
			CheckNumberProjectile = 0;
			// Запуск таймера стрельбы
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyAIPawn::Fire, 1, true, 1);
		}

	}
}

// Функция установит патрульные точки
void AEnemyAIPawn::SetPatrollingPoints(const TArray<ATargetPoint*>& NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}