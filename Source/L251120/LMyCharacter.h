// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon/WeaponName.h"
#include "GenericTeamAgentInterface.h"
#include "LMyCharacter.generated.h"

//UENUM(BlueprintType)
//enum class EWeaponState : uint8
//{
//	Unarmed = 0 UMETA(DisplayName = "Unarmed"),
//	Pistol = 10 UMETA(DisplayName = "Pistol"),
//	Rifle = 20 UMETA(DisplayName = "Rifle")
//};

UCLASS()
class L251120_API ALMyCharacter : public ACharacter , public IGenericTeamAgentInterface
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAnimMontage> HitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAnimMontage> DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UChildActorComponent> Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VALUE")
	TSubclassOf<class AWeaponBase> WeaponTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Run;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Reload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_IronSight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UInputAction> IA_Crouch;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", Replicated)
	float CurrentHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", Replicated)
	float MaxHP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated) //이거만 함
	uint8 bIsRun : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bLeftLean : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bRightLean : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bAiming : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	uint8 bCrouching : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	uint8 bIsFire : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	uint8 bIsIronSight : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim", Replicated)
	EWeaponState  WeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UParticleSystem> BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAIPerceptionStimuliSourceComponent> StimuliSource;

public:
	UFUNCTION(BlueprintCallable)
	void Move(float Forward, float Right);

	UFUNCTION(BlueprintCallable)
	void Look(float Pitch, float Yaw);

	UFUNCTION(BlueprintCallable)
	void StartRun();

	UFUNCTION(Server, Reliable)
	void C2S_StartRun();
	void C2S_StartRun_Implementation();

	UFUNCTION(BlueprintCallable)
	void StopRun();

	UFUNCTION(Server, Reliable)
	void C2S_StopRun();
	void C2S_StopRun_Implementation();

	UFUNCTION(BlueprintCallable)
	void StartCrouch();

	UFUNCTION(Server, Reliable)
	void C2S_StartCrouch();
	void C2S_StartCrouch_Implementation();

	/*UFUNCTION(BlueprintCallable)
	void StopCrouch();

	UFUNCTION(Server, Reliable)
	void C2S_StopCrouch();
	void C2S_StopCrouch_Implementation();*/

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(Server, Reliable)
	void C2S_Reload();
	void C2S_Reload_Implementation();

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

	UFUNCTION()
	virtual void SpawnHitEffect(const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	void DoDead();

	UFUNCTION(Server, Reliable)
	void C2S_DoDead();
	void C2S_DoDead_Implementation();

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

	UFUNCTION(Server, Reliable)
	void C2S_StartIronSight();
	void C2S_StartIronSight_Implementation();

	UFUNCTION(BlueprintCallable)
	void StopIronSight();


	UFUNCTION(Server, Reliable)
	void C2S_StopIronSight();
	void C2S_StopIronSight_Implementation();

	FRotator GetAimOffset() const;

	//----------------------------------------------------------------------//
	// IGenericTeamAgentInterface
	//----------------------------------------------------------------------//

	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& InTeamID) override;

	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const override;

	//----------------------------------------------------------------------//
	// IGenericTeamAgentInterface
	//----------------------------------------------------------------------//
private:
	FGenericTeamId TeamID;


public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
