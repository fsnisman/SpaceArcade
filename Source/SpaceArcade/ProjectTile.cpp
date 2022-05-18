/*
*  ����������
*/

#include "ProjectTile.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "PlayerShipPawn.h"

/*
*  ����
*/

// ������������ �������
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

// ������� ������ �������� 
void AProjectTile::Start()
{
	// ������ ������� ��� ������ ��������
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTile::Move, MoveRate, true, MoveRate);
	// ����������� ������� ��� ���������� ����������
	SetLifeSpan(FlyRange / MoveSpeed);
}

// ������� ����������� ������� � ������� ���������
void AProjectTile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//���������� �� ������
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// ���������� ���������
	AActor* owner = GetOwner();
	// ���������� ���������� ���������
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	
	// �������� �� ������
	if (playerShip == OtherActor)
	{
		return;
	}
	else
	{
		// ������ ����� �����
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffectPunch, GetActorLocation());

		// �������� ������� �� ���������
		if (OtherActor != owner && OtherActor != ownerByOwner)
		{
			// ���� �� �������� �����
			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
			// �������� �� �������� �������
			if (damageTakerActor)
			{
				// �������� ��������� ������
				FDamageData damageData;
				// ������ ����� � ����������
				damageData.DamageValue = Damage;
				// �������� �� ���������
				damageData.Instigator = owner;
				// �� ���� ����
				damageData.DamageMaker = this;

				// �������� �����
				damageTakerActor->TDamage(damageData);
			}
			else
			{
				// ���������� ������
				OtherActor->Destroy();
			}

			// �������� �� ������ ���� "SpecailCannon"
			if (!ActorHasTag(TEXT("SpecailCannon")))
			{
				// �������� �������
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollisionEffect, GetActorTransform());
				// ���������� ������
				Destroy();
			}
		}

	}
	
}

// ������� �������� 
void AProjectTile::Move()
{
	// ���������� �� ��������� �������
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	// �������� �� �������� �������
	SetActorLocation(nextPosition);
}