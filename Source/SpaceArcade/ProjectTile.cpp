/*
*  Библеотеки
*/

#include "ProjectTile.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "PlayerShipPawn.h"

/*
*  Код
*/

// Иницилизация объекта
AProjectTile::AProjectTile()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectTile::OnMeshOverlapBegin);

	LazerEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lazer"));
	LazerEffect->SetupAttachment(RootComponent);

	CollisionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Collision Effect"));

	AudioEffectPunch = CreateDefaultSubobject<USoundBase>(TEXT("Audio Punch effect"));
}

// Функция Начала движения 
void AProjectTile::Start()
{
	// Запуск таймера для начала движения
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTile::Move, MoveRate, true, MoveRate);
	// Уничтожение объекта при пройденном расстоянии
	SetLifeSpan(FlyRange / MoveSpeed);

	// Каст на глобальную ифнормацию
	UPlayerGameInstance* GameInstance = Cast<UPlayerGameInstance>(GetWorld()->GetGameInstance());

	// Обновление урона
	Damage *= GameInstance->UpgradeDamage;
}

// Функция пересечения объекта с другими объектами
void AProjectTile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Переменная на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Переменная владельца
	AActor* owner = GetOwner();
	// Переменная владеющего владельца
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	
	// Проверка на игрока
	if (playerShip == OtherActor)
	{
		return;
	}
	else
	{
		// Запуск звука удара
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectPunch, GetActorLocation());

		// Проверка объекта на владельца
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
				damageData.DamageValue = Damage;
				// Проверка на владельца
				damageData.Instigator = owner;
				// От кого урон
				damageData.DamageMaker = this;

				// Передача урона
				damageTakerActor->TDamage(damageData);
			}
			else
			{
				// Уничтожить объект
				OtherActor->Destroy();
			}

			// Проверка на наличе тега "SpecailCannon"
			if (!ActorHasTag(TEXT("SpecailCannon")))
			{
				// Создание эффекта
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionEffect, GetActorTransform());
				// Уничтожить снаряд
				Destroy();
			}
		}

	}
	
}

// Функция движения 
void AProjectTile::Move()
{
	// Переменная на следующую позицию
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	// Движения на слеюущую позицию
	SetActorLocation(nextPosition);
}