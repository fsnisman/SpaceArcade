
#include "ProjectTileEnemy.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "EnemyAIPawn.h"

AProjectTileEnemy::AProjectTileEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	//=========================
	// Create Root Component for ProjectTile
	//=========================

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	//=========================
	// Create HitCollider for ProjectTile
	//=========================

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(RootComponent);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectTileEnemy::OnMeshOverlapBegin);

	//=========================
	// Create Lazer Effect for Cannon
	//=========================

	BulletEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bullet"));
	BulletEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectTileEnemy::BeginPlay()
{
	Super::BeginPlay();
}


// Function Start for Projectile
void AProjectTileEnemy::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTileEnemy::Move, MoveRate, true, MoveRate);
	SetLifeSpan(FlyRange / MoveSpeed);
}

// Function Collision for Projectile
void AProjectTileEnemy::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	AProjectTileEnemy* FireSpecial = this;

	if (OtherActor == GetInstigator())
	{
		return;
	}

	if (FireSpecial->ActorHasTag(TEXT("FireSpecial")))
	{
		if (OtherActor != owner && OtherActor != ownerByOwner)
		{
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
			if (damageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = Damage;
				damageData.Instigator = owner;
				damageData.DamageMaker = this;

				damageTakerActor->TDamage(damageData);
			}
			else
			{
				OtherActor->Destroy();
			}
		}
	}
	else
	{
		if (OtherActor != owner && OtherActor != ownerByOwner)
		{
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
			if (damageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = Damage;
				damageData.Instigator = owner;
				damageData.DamageMaker = this;

				damageTakerActor->TDamage(damageData);

				Destroy();
			}
			else
			{
				OtherActor->Destroy();
			}
		}
	}
}

// Function Move for Projectile
void AProjectTileEnemy::Move()
{


	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}