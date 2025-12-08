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
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/BaseDamageType.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundCue.h"
#include "weapon/FloorWeaponBase.h"
#include "Components/DecalComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Net/UnrealNetwork.h"
#include "Login/LoginGS.h"
#include "Login/LoginGM.h"

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

	StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSource"));

	SetGenericTeamId(1);
}

// Called when the game starts or when spawned
void ALMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//무기 집으면 잡게끔 이동 시킬 것 (지금은 간단히.)
	
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
		UIC->BindAction(IA_Run, ETriggerEvent::Started, this, &ALMyCharacter::StartRun);
		UIC->BindAction(IA_Run, ETriggerEvent::Completed, this, &ALMyCharacter::StopRun);

		UIC->BindAction(IA_Reload, ETriggerEvent::Completed, this, &ALMyCharacter::C2S_Reload);
		UIC->BindAction(IA_Fire, ETriggerEvent::Started, this, &ALMyCharacter::StartFire);
		UIC->BindAction(IA_Fire, ETriggerEvent::Completed, this, &ALMyCharacter::StopFire);
		UIC->BindAction(IA_IronSight, ETriggerEvent::Started, this, &ALMyCharacter::StartIronSight);
		UIC->BindAction(IA_IronSight, ETriggerEvent::Completed, this, &ALMyCharacter::StopIronSight);

		UIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &ALMyCharacter::StartCrouch);
		//UIC->BindAction(IA_Crouch, ETriggerEvent::Completed, this, &ALMyCharacter::StopRun);
	}
}

void ALMyCharacter::OnRep_CurrentHP(const float InHP)
{
	OnChangeHP.Broadcast(CurrentHP / MaxHP);
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

void ALMyCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f; //서버시간 때문에 느려보이지 않을려고 -> 반응성이 좋아지게 하기 위해서
	C2S_StartRun();
}

void ALMyCharacter::C2S_StartRun_Implementation()
{
	bIsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ALMyCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	C2S_StopRun();
}

void ALMyCharacter::C2S_StopRun_Implementation()
{
	bIsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ALMyCharacter::StartCrouch()
{
	bCrouching = CanCrouch();
	if (bCrouching)
	{
		Crouch();
		C2S_StartCrouch();
		return;
	}
	UnCrouch();
	C2S_StartCrouch();
}


void ALMyCharacter::C2S_StartCrouch_Implementation()
{
	bCrouching = CanCrouch();
	if (bCrouching)
	{
		Crouch();
		return;
	}
	UnCrouch();
}

//void ALMyCharacter::StopCrouch()
//{
//	UnCrouch();
//
//	C2S_StopCrouch_Implementation();
//}
//
//void ALMyCharacter::C2S_StopCrouch_Implementation()
//{
//	UnCrouch();
//}

//맘에 안듬..
//bIsReload 만들어서 ABP에 박아 넣는 방식이 더 깔끔할 거 같은데
//일단 보류..
void ALMyCharacter::Reload()
{
	C2S_Reload();
}

void ALMyCharacter::C2S_Reload_Implementation()
{
	S2A_Reload();
}

void ALMyCharacter::S2A_Reload_Implementation()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		PlayAnimMontage(ChildWeapon->ReloadMontage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No ChildWeapon"));
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

	S2A_HitReact();
}

void ALMyCharacter::S2A_HitReact_Implementation()
{
	int32 RandInteger = FMath::RandRange(0, 7);
	FName RandName[8] = {
	"Back_01", "Front_01", "Front_02",
	"Front_03", "Front_04", "Front_05",
	"Front_06", "Front_07"
	};

	PlayAnimMontage(HitMontage, 1.0f, RandName[RandInteger]);
}

void ALMyCharacter::ReloadWeapon()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Reload();
	}
}

void ALMyCharacter::StartFire()
{
	bIsFire = true;
	C2S_StartFire();
}

void ALMyCharacter::C2S_StartFire_Implementation()
{
	bIsFire = true;
	DoFire();
}

void ALMyCharacter::DoFire()
{
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->Fire();
	}
}

void ALMyCharacter::StopFire()
{
	bIsFire = false;
	C2S_StopFire();
}

void ALMyCharacter::C2S_StopFire_Implementation()
{
	bIsFire = false;
	AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());
	if (ChildWeapon)
	{
		ChildWeapon->StopFire();
	}
}

float ALMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* Event = (FPointDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurrentHP -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Point Damage %f %s"), CurrentHP, *(Event->HitInfo.BoneName.ToString()));
		}
		S2A_SpawnHitEffect(Event->HitInfo);
	}
	else if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* Event = (FRadialDamageEvent*)(&DamageEvent);
		if (Event)
		{
			CurrentHP -= DamageAmount;
			UE_LOG(LogTemp, Warning, TEXT("Radial Damage %f %s"), CurrentHP, *Event->DamageTypeClass->GetName());
		}
	}
	else
	{
		CurrentHP -= DamageAmount;
	}

	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHP);
	S2A_HitReact();

	if (CurrentHP <= 0 ) //&& bIsDead == false
	{
		ALoginGM* GM = Cast<ALoginGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			GM->CheckAliveCount();
		}

		S2A_DeadAnime();

		DoDead();
	}

	/*UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		BloodEffect,
		this->GetActorLocation(),

		);
	this->AddControllerPitchInput(-0.05f);*/

	if (HasAuthority())
	{
		OnRep_CurrentHP(CurrentHP / MaxHP);
	}

	return 0.0f;
}

void ALMyCharacter::SpawnHitEffect(const FHitResult& Hit)
{
	if (BloodEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BloodEffect,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation()
		);
	}
}

void ALMyCharacter::S2A_SpawnHitEffect_Implementation(const FHitResult& Hit)
{
	if (BloodEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BloodEffect,
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation()
		);
	}
}

void ALMyCharacter::DoDead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	C2S_DoDead();
}

void ALMyCharacter::C2S_DoDead_Implementation()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	bIsDead = true;
}

void ALMyCharacter::S2A_DeadAnime_Implementation()
{
	FString SectionName = FString::Printf(TEXT("%d"), FMath::RandRange(1, 8));
	PlayAnimMontage(DeathMontage, 1.0f, FName(*SectionName));
}

void ALMyCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (!PC || !PC->HasAuthority())
	{
		return;
	}

	AFloorWeaponBase* TempWeapon = Cast<AFloorWeaponBase>(OtherActor);
	if (TempWeapon)
	{
		Weapon->SetChildActorClass(TempWeapon->WeaponTemplate);

		AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());

		if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::Pistol)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Pistol;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::Rifle)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Rifle;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::GrenadeLauncher)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Rifle;
			ChildWeapon->SetOwner(this);
		}

		if (!TempWeapon->bIsInfinity)
		{
			TempWeapon->Destroy();
		}

		TempWeapon->SetOwner(this);

	}

}

void ALMyCharacter::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	/*APlayerController* PC = Cast<APlayerController>(GetController());

	if (!PC || !PC->HasAuthority())
	{
		return;
	}

	AFloorWeaponBase* TempWeapon = Cast<AFloorWeaponBase>(OtherActor);
	if (TempWeapon)
	{
		Weapon->SetChildActorClass(TempWeapon->WeaponTemplate);

		AWeaponBase* ChildWeapon = Cast<AWeaponBase>(Weapon->GetChildActor());

		if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::Pistol)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Pistol;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::Rifle)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Rifle;
			ChildWeapon->SetOwner(this);
		}
		else if (ChildWeapon && TempWeapon->WeaponState == EWeaponState::GrenadeLauncher)
		{
			ChildWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, ChildWeapon->SocketName);
			WeaponState = EWeaponState::Rifle;
			ChildWeapon->SetOwner(this);
		}

		if (!TempWeapon->bIsInfinity)
		{
			TempWeapon->Destroy();
		}

		TempWeapon->SetOwner(this);

	}*/
}

void ALMyCharacter::UseItme(AActor* PickedUpItem)
{
}

void ALMyCharacter::EatItme(AActor* PickedUpItem)
{
}

void ALMyCharacter::EquipItme(AActor* PickedUpItem)
{
}

void ALMyCharacter::StartIronSight()
{
	bIsIronSight = true;
	C2S_StartIronSight_Implementation();
}

void ALMyCharacter::C2S_StartIronSight_Implementation()
{
	bIsIronSight = true;
}

void ALMyCharacter::StopIronSight()
{
	bIsIronSight = false;
	C2S_StopIronSight_Implementation();
}

void ALMyCharacter::C2S_StopIronSight_Implementation()
{
	bIsIronSight = false;
}

FRotator ALMyCharacter::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void ALMyCharacter::SetGenericTeamId(const FGenericTeamId& InTeamID)
{
	TeamID = InTeamID;
}

FGenericTeamId ALMyCharacter::GetGenericTeamId() const
{
	return TeamID;
}

void ALMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALMyCharacter, bIsRun);
	DOREPLIFETIME(ALMyCharacter, bLeftLean);
	DOREPLIFETIME(ALMyCharacter, bRightLean);
	DOREPLIFETIME(ALMyCharacter, bAiming);
	DOREPLIFETIME(ALMyCharacter, bCrouching);
	DOREPLIFETIME(ALMyCharacter, bIsFire);
	DOREPLIFETIME(ALMyCharacter, bIsIronSight);
	DOREPLIFETIME(ALMyCharacter, bIsDead);

	DOREPLIFETIME(ALMyCharacter, CurrentHP);
	DOREPLIFETIME(ALMyCharacter, MaxHP); 

	DOREPLIFETIME(ALMyCharacter, WeaponState);

}

