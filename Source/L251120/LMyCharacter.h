// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponName.h"
#include "LMyCharacter.generated.h"

//UENUM(BlueprintType)
//enum class EWeaponState : uint8
//{
//	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
//	Pistol = 10 UMETA(DisplayName = "Pistol"),
//	Rifle = 20 UMETA(DisplayName = "Rifle")
//};

UCLASS()
class L251120_API ALMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr <class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsRun : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bLeftLean : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bRightLean : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bAiming : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	EWeaponState  WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bCrouching : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UChildActorComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VALUE")
	TSubclassOf<class AWeaponBase> WeaponTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_IronSight;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bIsFire : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	uint8 bIsIronSight : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UParticleSystem> BloodEffect;

public:
	UFUNCTION(BlueprintCallable)
	void Move(float Forward, float Right);

	UFUNCTION(BlueprintCallable)
	void Look(float Pitch, float Yaw);

	UFUNCTION(BlueprintCallable)
	void RunTrigger();

	UFUNCTION(BlueprintCallable)
	void CrouchTrigger();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void HitReact();

	UFUNCTION(BlueprintCallable)
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	void DoFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(BlueprintCallable)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void UseItme(AActor* PickedUpItem);

	UFUNCTION(BlueprintCallable)
	void EatItme(AActor* PickedUpItem);

	UFUNCTION(BlueprintCallable)
	void EquipItme(AActor* PickedUpItem);

	UFUNCTION(BlueprintCallable)
	void StartIronSight();

	UFUNCTION(BlueprintCallable)
	void StopIronSight();
};
