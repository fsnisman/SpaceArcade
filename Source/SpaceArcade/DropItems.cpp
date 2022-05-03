#include "DropItems.h"


ADropItems::ADropItems()
{
	PrimaryActorTick.bCanEverTick = true;

	//=========================
	// Create Static Mesh for Ship
	//=========================

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drop body"));
	RootComponent = BodyMesh;

	//=========================
	// Create Hit Colloder for Ship
	//=========================

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ADropItems::OnMeshOverlapBegin);

	//=========================
	// Create Shoot Effect for Cannon
	//=========================

	LightEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lighting effect"));
	LightEffect->SetupAttachment(BodyMesh);

	//=========================
	// Create Audio Effect for Exlosion
	//=========================

	AudioEffect = CreateDefaultSubobject<USoundBase>(TEXT("Audio effect pickup"));
}

void ADropItems::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADropItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropItems::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(5, 3, FColor::Blue, FString::Printf(TEXT("Overlaping")));

	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	if (OtherActor != playerShip)
	{
		GEngine->AddOnScreenDebugMessage(6, 3, FColor::Red, FString::Printf(TEXT("Fail Overlaping")));
		return;
	}

	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		GEngine->AddOnScreenDebugMessage(7, 3, FColor::Green, FString::Printf(TEXT("Done Overlaping")));
		if (this->ActorHasTag(TEXT("Coin")))
		{
			GEngine->AddOnScreenDebugMessage(8, 3, FColor::Yellow, FString::Printf(TEXT("Coin Overlaping")));
			playerState->Coin += DropCountCoin;
			Destroy();
		}

		if (this->ActorHasTag(TEXT("LevelUP")))
		{
			GEngine->AddOnScreenDebugMessage(9, 3, FColor::Cyan, FString::Printf(TEXT("Level Up Overlaping")));
			if (playerState->LevelShip < 3)
			{
				playerState->LevelShip += DropCountLevelUP;
			}
			else
			{
				playerState->Coin = DropCountCoin;
			}

			Destroy();
		}

		if (this->ActorHasTag(TEXT("Sharp")))
		{
			GEngine->AddOnScreenDebugMessage(10, 3, FColor::Purple, FString::Printf(TEXT("Sharpe Overlaping")));
			playerState->Sharp += DropCountSharp;
			Destroy();
		}
	}
}