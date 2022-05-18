/*
*  Библеотеки
*/

#include "DropItems.h"

/*
*  Код
*/

// Иницилизация объекта
ADropItems::ADropItems()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drop body"));
	RootComponent = BodyMesh;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);
	HitCollider->OnComponentBeginOverlap.AddDynamic(this, &ADropItems::OnMeshOverlapBegin);

	LightEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Lighting effect"));
	LightEffect->SetupAttachment(BodyMesh);

	AudioEffect = CreateDefaultSubobject<USoundBase>(TEXT("Audio effect pickup"));
}

// Пересечения объекта с другими объектами
void ADropItems::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//x GEngine->AddOnScreenDebugMessage(5, 3, FColor::Blue, FString::Printf(TEXT("Overlaping")));

	// Каст на игрока
	APlayerShipPawn* playerShip = Cast<APlayerShipPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	// Каста на данные игрока
	ABalancePlayerState* playerState = Cast<ABalancePlayerState>(playerShip->GetPlayerState());

	// Переменная владельца
	AActor* owner = GetOwner();
	// Переменная владеющего владельца
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;

	// Проверка на игрока
	if (OtherActor != playerShip)
	{
		//x GEngine->AddOnScreenDebugMessage(6, 3, FColor::Red, FString::Printf(TEXT("Fail Overlaping")));
		return;
	}

	// Проверка на владельца
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		//x GEngine->AddOnScreenDebugMessage(7, 3, FColor::Green, FString::Printf(TEXT("Done Overlaping")));
		// Проверка на наличе тега "Coin"
		if (this->ActorHasTag(TEXT("Coin")))
		{
			//x GEngine->AddOnScreenDebugMessage(8, 3, FColor::Yellow, FString::Printf(TEXT("Coin Overlaping")));
			// Проигрывание звука
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffect, GetActorLocation());
			// Запись прибалвение монетки
			playerState->Coin += DropCountCoin;
			// Уничтожение
			Destroy();
		}
		// Проверка на наличе тега "LevelUP"
		if (this->ActorHasTag(TEXT("LevelUP")))
		{
			//x GEngine->AddOnScreenDebugMessage(9, 3, FColor::Cyan, FString::Printf(TEXT("Level Up Overlaping")));
			// Проверка на максимальный уровень
			if (playerState->LevelShip < 3)
			{
				// Проигрывание звука
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffect, GetActorLocation());
				// Запись прибалвение улечшения
				playerState->LevelShip += DropCountLevelUP;
			}
			else
			{
				// Проиграывание звка
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffect, GetActorLocation());
				// Запись прибалвение монет
				playerState->Coin += DropCountCoin;
			}
			// Уничтоежние
			Destroy();
		}
		// Проверка на наличе тега "Sharp"
		if (this->ActorHasTag(TEXT("Sharp")))
		{
			//x GEngine->AddOnScreenDebugMessage(10, 3, FColor::Purple, FString::Printf(TEXT("Sharpe Overlaping")));
			// Проигрывание звука
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), AudioEffect, GetActorLocation());
			// Запись прибалвение шарпов
			playerState->Sharp += DropCountSharp;
			// Уничтожения
			Destroy();
		}
	}
}