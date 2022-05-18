/*
*	Класс Enemy AI Pawn пешка врага.
*/

#pragma once

/*
*  Библеотеки
*/

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Engine/TargetPoint.h"

#include "DamageTaker.h"
#include "HealthComponent.h"
#include "ProjectTileEnemy.h"
#include "PlayerShipPawn.h"
#include "DropItems.h"

#include "Components/WidgetComponent.h"
#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"


#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "EnemyAIPawn.generated.h"

/*
*  Класс
*/

class AAIEnemyController;
class UStaticMeshComponent;
class USpringArmComponent;
class UHealthComponent;
class UCameraComponent;
class UBoxComponent;


UCLASS()
class SPACEARCADE_API AEnemyAIPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Компоненты

	// Компонент тела 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	// Компонент материала
	UPROPERTY(EditAnywhere, Category = "Materials")
		UMaterialInterface* MaterialOne;

	// Компонент материала
	UPROPERTY(EditAnywhere, Category = "Materials")
		UMaterialInterface* MaterialTwo;

	// Компонент материала
	UPROPERTY(EditAnywhere, Category = "Materials")
		UMaterialInterface* MaterialThree;

	// Компонент колайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	// Компонент колайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider2;

	// Компонент колайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider3;

	// Компонент здоровья
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	// Компонент направление стрельбы
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	// Компонент партикла стрельбы
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffect;

	// Компонент пратика особого выстрела
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* SpecialShootEffect;

	// Комонент партикла двигателя
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect;

	// Компонент партикла двигателя
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect2;

	// Копмопонент партикла линия воздуха
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect;

	// Копмопонент партикла линия воздуха
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect2;

	// Компонент партикла взрыва
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ExlosionEffectDie;

	// Компонент партикла взрыва
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* FireExlosionEffectDie;

	// Копонент партикла взрыва
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystem* ExlosionEffect;

	// Компонент звука стрельбы
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	// Компонент звука удара
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffectPunch;

	// Компонент звук взрыва
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		USoundBase* AudioEffectDie;

	// Компонент виджета прогресс бара для здоровья
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
		UWidgetComponent* BarHP;

	//////////////////////////
	//// Переменные

	// Массив снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass;

	// Массив снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass2;

	// Массив снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClass3;

	// Массив особенного снаряда
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTileEnemy> ProjectileClassSpecial;

	// Массив патруль точек
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;

	// Контроллер врага
	UPROPERTY()
		AAIEnemyController* EnemyShipController;

	// Массив вещей
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop")
		TSubclassOf<ADropItems> DropItem;

	// Дальность стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	// Частота стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireFrequency = 5;

	// Количество выстрелов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int CountFire = 0;

	// Стрельба в игрока
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		bool bFireToPlayer = true;

	// Скорость движения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 100.f;

	// Скорость поворота
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100.f;

	// Частота движения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy") // AI Movement Accurency
		float MovementAccurancy = 100;

	// Сглаживания движения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float ForwardSmootheness = 0.1f;

	// Сглаживания поворота
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSmootheness = 0.1f;

	// Время стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timer Fire")
		float fTimerFire = 1;

	// Проверка на два направление стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bTwoProjectTile = 0;

	// Проверка на разрборс направление стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bScatterProjectTile = false;

	// Количество снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		int CountProjectTile = 0;

	// Разрброс напрвление стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		int ScatterProjectTile = 0;

	// Проверка на поворт напрвление стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setting ProjectTile")
		bool bProjectileRotate360 = true;

	// Проверка на слежение направление за игроком
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tracking from Player")
		bool bTrackingPlayerArrow = true;

	// Проверка на слежение корабля за игроком
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tracking from Player")
		bool bTrackingPlayerShip = true;

	// Урона от взрыва
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion Damage")
		float ExplosionDamage = 1;

	// Урона от взрыва для врага
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion Damage")
		float ExplosionDamageEnemy = 1;

	// Минимальное значение очков после уничтожения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score")
		float ScoreDeathMin = 0;
	
	// Максимальное значение очков после уничтожения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score")
		float ScoreDeathMax = 0;

	// Значение монет после уничтожения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropCoin = 0;

	// Значение улучшение после уничтожения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropLevelUP = 0;
	
	// Значение шарпов после уничтожения
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop | Drop Count")
		float DropSharp = 0;

	// Значение таймера
	FTimerHandle TimerHandle; //Timer

	// Значение направления
	int Direction = 1;

protected:

	//////////////////////////
	//// Функции

	// Начало действия при создании объекта
	virtual void BeginPlay() override;

	// Функция уничтожения объекта
	UFUNCTION()
		void Die();

	// Функция получение лога от урона
	UFUNCTION()
		void DamageTaked(float DamageValue);

	// Функция пересечения объекта с другими объектами
	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult); // Collision 

public:

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	AEnemyAIPawn();

	// Функция получени частоты движения
	UFUNCTION()
		float GetMovementAccurancy()
	{
		return MovementAccurancy;
	};

	// Функция стрельбы
	UFUNCTION()
		void Fire();

	// Функция стрельбы босса
	UFUNCTION()
		void FireBoss();

	// Функция стрельбы 360 градусов
	UFUNCTION()
		void Fire360();

	// Функция особой стрельбы
	UFUNCTION()
		void FireSpecial();

	// Функция получение урона
	UFUNCTION()
		bool TDamage(FDamageData DamageData);
	
	// Функция получени направление движения
	UFUNCTION()
		FVector GetArrowForwardVector();

	// Функция повопрота напрвелния движения
	UFUNCTION()
		void RotateArrowTo(FVector TargetPosition);

	// Функция таймера стрельбы
	UFUNCTION()
		void TimerFire();

	// Функция остановки движения
	UFUNCTION()
		void StopMove();

	// Функция установит патрульные точки
	UFUNCTION()
		void SetPatrollingPoints(const TArray <ATargetPoint*>& NewPatrollingPoints);

	// Функция массива патрульных точек
	UFUNCTION()
		TArray<FVector> GetPatrollingPoints();

	// Функция получение текущего здоровья
	UFUNCTION()
		float GetCurretHealth();

	// Функция получение максимального значение здоровья
	UFUNCTION()
		float GetMaxHealth();

	// Фукнция включение коллизии
	void EnableCollision();

	// Получени координат напавления стрельбы
	FVector GetEyesPosition();

	// Обновление объекта в каждом тике
	virtual void Tick(float DeltaTime) override;

	// Установка компонента ввода врага
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Функция привязки значение движение
	float FMovementComponent(float ValueAxis);

	// Функция привязки Значение поворота
	float FRotationComponent(float ValueAxis);

	//////////////////////////
	//// Переменные

	// Переменная на массив камер шейк
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShake;

	// Проверка на изменине материла
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Material")
		bool tbSetMaterial = false;

	// Массив дропов
	TSubclassOf<ADropItems> dDropItem;

	// Значение таргета на движение 
	float TargetForwardAxisValue = 0.f;
	// Значение таргета на поворота
	float TargetRightAxisValue = 0.f;
	// Значение текущего поворота
	float CurrentRightAxisValue = 0.f;
	// Значение текущего на движение 
	float CurrentForwardAxisValue = 0.f;
	// Значение сколько снарядов выпущено
	float CheckNumberProjectile = 0;
	
	// Значение остановки двжиения
	float ValueTimerStopMove = 0;
	// Значение скосрости движения
	float fMoveSpeed = 0;
	// Значение скорости поворота
	float FRotationSpeed = 0;
	// Значение частоты движения
	float FMovementAccurancy = 0;
	// Значение сглаживание движения
	float FForwardSmootheness = 0;
	// Значение сглаживание поворота
	float FRotationSmootheness = 0;
	// Значение таймера для стрельбы
	float FfTimerFire = 0;

	// Значение снарядов
	int iCountProjectTile = 0;

	// Вектороное значение напралвение 
	FVector ArrowTarget;

	// Проверка на поворт навправления
	bool tbRotateArrow = false;
	// Прверка на остановку корабля
	bool tbStoppedMove = true;
	// Проверка на поворот корабля
	bool tbRotateShip = false;
	// Проверка на поворт корабля за игроком
	bool tbRotateShipToPlayer = false;
	// Проверка на движение задом
	bool tbBackMoveShip = false;
	// Проверка на коллизую врага
	bool CheckCollisionEnemy = true;
	// Проверка на готовность стрельбы
	bool ReadyFire = true;
};
