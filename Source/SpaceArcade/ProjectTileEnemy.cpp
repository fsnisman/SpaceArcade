/*
*  ����������
*/

#include "ProjectTileEnemy.h"
#include "DamageTaker.h"
#include "TimerManager.h"
#include "EnemyAIPawn.h"

/*
*  ���
*/

// ������������ �������
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

// ������� ������ �������� 
void AProjectTileEnemy::Start()
{
	// ������ ������� ��� ������ ��������
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this, &AProjectTileEnemy::Move, MoveRate, true, MoveRate);
	// ����������� ������� ��� ���������� ����������
	SetLifeSpan(FlyRange / MoveSpeed);
}

// ������� ����������� ������� � ������� ���������
void AProjectTileEnemy::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ���������� ���������
	AActor* owner = GetOwner();
	// ���������� ���������� ���������
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	// ���������� ���������� �������
	AProjectTileEnemy* FireSpecial = this;

	// �������� �� ������������ ������
	if (OtherActor == GetInstigator())
	{
		return;
	}

	// �������� �� ������ ���� "FireSpecial"
	if (FireSpecial->ActorHasTag(TEXT("FireSpecial")))
	{
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
		}
	}
	else
	{	// �������� ������� �� ���������
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

				// ����������� �������
				Destroy();
			}
			else
			{
				// ����������� �������
				OtherActor->Destroy();
			}
		}
	}
}

// ������� �������� 
void AProjectTileEnemy::Move()
{
	// ���������� �� ��������� �������
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed * MoveRate;
	// �������� �� �������� �������
	SetActorLocation(nextPosition);
}