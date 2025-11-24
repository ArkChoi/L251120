// Fill out your copyright notice in the Description page of Project Settings.


#include "LMyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ChildActorComponent.h"
#include "EnhancedInputComponent.h"
#include "Weapon/WeaponBase.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ALMyCharacter::ALMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SocketOffset = FVector(0, 0, 0);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0,0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ALMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//무기 집으면 잡게끔 이동 시킬 것 (지금은 간단히.)
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
		WeaponState = EWeaponState::Pistol;
	}
	
}

// Called every frame
void ALMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Reload, ETriggerEvent::Completed, this,
			&ALMyCharacter::Reload);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this,
			&ALMyCharacter::DoFire);
	}
}

void ALMyCharacter::Move(float Forward, float Right)
{
	const FRotator CameraRotation = GetController()->GetControlRotation();
	const FRotator YawRotation = FRotator(0, CameraRotation.Yaw, 0);
	const FRotator YawRollRotation = FRotator(0, CameraRotation.Yaw, CameraRotation.Roll);

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);
	AddMovementInput(ForwardVector, Forward);

	//Right 구현
	const FVector RightVector = UKismetMathLibrary::GetRightVector(YawRollRotation);
	AddMovementInput(RightVector, Right);
}

void ALMyCharacter::Look(float Pitch, float Yaw)
{
	AddControllerPitchInput(Pitch);
	AddControllerYawInput(Yaw);
}

void ALMyCharacter::RunTrigger()
{
	bIsRun = (!bIsRun);
	if (bIsRun)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		return;
	}
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ALMyCharacter::CrouchTrigger()
{
	bCrouching = CanCrouch();
	if (bCrouching)
	{
		Crouch();
		return;
	}
	UnCrouch();
}


void ALMyCharacter::Reload() 
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		PlayAnimMontage(ChildWeapon->ReloadMontage);
	}
}

void ALMyCharacter::HitReact()
{
	int32 RandInteger = FMath::RandRange(0,7);
	FName RandName[8] = {
	"Back_01", "Front_01", "Front_02",
	"Front_03", "Front_04", "Front_05",
	"Front_06", "Front_07"
	};
	//FString SectionName = FString::Printf(TEXT("%d"), FMath::RandRange(1, 8)); //위 코드와 같은 동작이나.. 이름이 1,2,3,4,... 로 되어 있어야 한다

	PlayAnimMontage(HitMontage,1.0f ,RandName[RandInteger]);
	//PlayAnimMontage(HitMontage, 1.0f, FName(*SectionName)); //위 코드와 같은 동작이나.. 이름이 1,2,3,4,... 로 되어 있어야 한다
	
}

void ALMyCharacter::ReloadWeapon()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Reload();
	}
}

void ALMyCharacter::DoFire()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Fire();
	}
}

