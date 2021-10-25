#include "PlayerShipPawn.h"

APlayerShipPawn::APlayerShipPawn()
{
 	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ship body"));
	RootComponent = BodyMesh;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	ProjectTileSetupArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Project Tile Setup 1"));
	ProjectTileSetupArrow->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	/*HealthComponent->OnDie.AddDynamic(this, &APlayerShipPawn::Die);
	HealthComponent->OnDamaged.AddDynamic(this, &APlayerShipPawn::DamageTaked);*/

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerShipPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

//bool APlayerShipPawn::TDamage(FDamageData DamageData)
//{
//	return HealthComponent->TakeDamage(DamageData);
//}

//void APlayerShipPawn::Die()
//{
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.bNoFail = true;
//	Destroy();
//}

//void APlayerShipPawn::DamageTaked(float DamageValue)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
//}

void APlayerShipPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerShipPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

