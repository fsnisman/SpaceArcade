/*
*	Класс Player Ship Pawn пешка игрока.
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
#include "ProjectTile.h"
#include "BalancePlayerState.h"
#include "PlayerGameInstance.h"

#include <Camera/CameraComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

#include "PlayerShipPawn.generated.h"

/*
*  Класс
*/

class UStaticMeshComponent;
class USpringArmComponent;
class UHealthComponent;
class UCameraComponent;
class UBoxComponent;
class UMatineeCameraShake;


UCLASS()
class SPACEARCADE_API APlayerShipPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:

	//////////////////////////
	//// Компоненты

	// Компонент тела пешки
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UStaticMeshComponent* BodyMesh;

	// Компонент рычага
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		USpringArmComponent* SpringArm;

	// Компонент камеры
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UCameraComponent* Camera;

	// Компонент колайдера боксового
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components") 
		UBoxComponent* HitCollider;

	// Компонент здоровья
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	// Компонент напрвления спавна снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointOne;

	// Компонент напрвления спавна снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointTwo;

	// Компонент напрвления спавна снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPointSpecial;

	// Компонент партикла двигателя
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect;

	// Компонент партикла двигателя
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* EngineEffect2;

	// Компонент партикла линия полета
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect;

	// Компонент партикла линия полета
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* LineFlyEffect2;

	// Компонент партикла снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectOne;

	// Компонент партикла снаряда
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* ShootEffectTwo;

	// Компонент звука стрельбы
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffect;

	// Компонент звука особенной стрельы
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffectSpecial;

	// Компонент звука смерти
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
		USoundBase* AudioEffectDie;

	// Компонент эффекта взрыва
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystem* ExlosionEffect;

	// Компонент звука удара
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioEffectPunch;

	//////////////////////////
	//// Переменные

	// Переменная определяющая тип снаряда
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		EProjectType Type = EProjectType::FireProjectile;

	// Переменная массив снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTile> ProjectileClass;

	// Переменная массив особых снарядов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectTile> ProjectileClassSpecial;

	// Переменная дальность действия стельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	// Переменная частота стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float SecondTime = 1.f;

	// Переменная сглаживания полета
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FrequencyTime = 1.f;

	// Переменая таймера стрельбы
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireTimer = 0;

	// Пременная скорости движения по X
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeedX = 1.f;

	// Переменная скорости движения по Y
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeedY = 1.f;

	// Переменная уровня корабля
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level Ship")
		int LevelShip = 1;

	// Переменная смерти корабля игрока
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool DiedShip = false;

	// Переменная таймера
	FTimerHandle TimerHandle;

protected:

	//////////////////////////
	//// Функции

	// Начало действий при создании объекта
	virtual void BeginPlay() override;

	// Функция смерти
	UFUNCTION()
		void Die();

	// Функция отображение здоровья в логах
	UFUNCTION()
		void DamageTaked(float DamageValue);

	// Функция стрельбы 
	UFUNCTION()
		void Fire();

	//////////////////////////
	//// Переменные

	// Массив камеры шейк
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShake;

	// Массив камеры шейк при начале игры
	UPROPERTY(EditAnywhere)
		TSubclassOf<UMatineeCameraShake> CamShakeStart;

public:

	//////////////////////////
	//// Переменные

	// Количество уничтоженых врагов
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Count Died Enemy")
		float CountDiedEnemyPawn = 0;

	// Уровнь пройден
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LevelComplited")
		bool LevelComplitet = false;

	// Проверка на активный виджет меню
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool bActiveMenuWidget = false;


	// Готовность стрельбы
	bool ReadyFire = true;
	
	// Триггер на виджет с виньеткой
	bool TriggerVingget = false;

	// Триггер на спавн текста босса
	bool SpawnTextFightBoss = false;
	

	//////////////////////////
	//// Функции

	// Иницилизация объекта
	APlayerShipPawn();

	// Фнукция получения урона
	UFUNCTION()
		bool TDamage(FDamageData DamageData);

	// Функция получени текущего значения здоровья
	UFUNCTION()
		float GetCurretHealth();

	// Функция получени максимального значения здоровья
	UFUNCTION()
		float GetMaxHealth();

	// Функция стрельбы особым оружием
	UFUNCTION()
		void FireSpecial();

	// Фукнция готовности стрельбы
	UFUNCTION()
		void OnRedyOfFire();

	// Обновление объекта в каждом тике
	virtual void Tick(float DeltaTime) override;

	// Установка компонента ввода игрока
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
