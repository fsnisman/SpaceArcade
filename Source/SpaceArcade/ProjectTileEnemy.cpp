/*
*  Библеотеки
*/

#include "ProjectTileEnemy.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "EnemyAIPawn.h"

/*
*  Код
*/

// Иницилизация объекта
AProjectTileEnemy::AProjectTileEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectTileEnemy::OnMeshOverlapBegin);

	BulletEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bullet"));
	BulletEffect->SetupAttachment(RootComponent);
}

// Функция Начала движения 
void AProjectTileEnemy::Start()
{
	// Запуск таймера для начала движения
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTileEnemy::Move, MoveRate, true, MoveRate);
	// Уничтожение объекта при пройденном расстоянии
	SetLifeSpan(FlyRange / MoveSpeed);
}

// Функция пересечения объекта с другими объектами
void AProjectTileEnemy::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Переменная владельца
	AActor* owner = GetOwner();
	// Переменная владеющего владельца
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	// Переменная особенного снаряда
	AProjectTileEnemy* FireSpecial = this;

	// Проверка на выпускающего снаряд
	if (OtherActor == GetInstigator())
	{
		return;
	}

	// Проверка на наличе тега "FireSpecial"
	if (FireSpecial->ActorHasTag(TEXT("FireSpecial")))
	{
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
				// Унчитожить объект
				OtherActor->Destroy();
			}
		}
	}
	else
	{	// Проверка объекта на владельца
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

				// Уничтожение снаряда
				Destroy();
			}
			else
			{
				// Уничтожение объекта
				OtherActor->Destroy();
			}
		}
	}
}

// Функция движения 
void AProjectTileEnemy::Move()
{
	// Переменная на следующую позицию
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	// Движения на слеюущую позицию
	SetActorLocation(nextPosition);
}