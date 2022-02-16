
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
	HitCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

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

	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());

	if (OtherActor == GetInstigator())
	{
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "Enemy Ship");

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

			Destroy();
		}

	}

}

// Function Move for Projectile
void AProjectTileEnemy::Move()
{


	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}