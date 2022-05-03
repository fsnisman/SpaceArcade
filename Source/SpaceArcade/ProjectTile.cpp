
#include "ProjectTile.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "PlayerShipPawn.h"

AProjectTile::AProjectTile()
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
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectTile::OnMeshOverlapBegin);

	//=========================
	// Create Lazer Effect for Cannon
	//=========================

	LazerEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lazer"));
	LazerEffect->SetupAttachment(RootComponent);

	//=========================
	// Create Collision Effect for Cannon
	//=========================

	CollisionEffect = CreateDefaultSubobject<UParticleSystem>(TEXT("Collision Effect"));

	//=========================
	// Create Audio Effect for Punch
	//=========================

	AudioEffectPunch = CreateDefaultSubobject<USoundBase>(TEXT("Audio Punch effect"));
}

void AProjectTile::BeginPlay()
{
	Super::BeginPlay();
}

	// Function Start for Projectile
void AProjectTile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTile::Move, MoveRate, true, MoveRate);
	SetLifeSpan(FlyRange / MoveSpeed);
}

	// Function Collision for Projectile
void AProjectTile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (playerShip == OtherActor)
	{
		return;
	}
	else
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectPunch, GetActorLocation());

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

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionEffect, GetActorTransform());
			Destroy();
		}

	}
	
}

	// Function Move for Projectile
void AProjectTile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	SetActorLocation(nextPosition);
}