// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LMyCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
	Pistol = 10 UMETA(DisplayName = "Pistol"),
	Rifle = 20 UMETA(DisplayName = "Rifle")
};

UENUM(BlueprintType)
enum class EHitState : uint8
{
	Back_01 = 0,
	Front_01 = 1,
	Front_02 = 2,
	Front_03 = 3,
	Front_04 = 4,
	Front_05 = 5,
	Front_06 = 6,
	Front_07 = 7
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Reload;

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
};
