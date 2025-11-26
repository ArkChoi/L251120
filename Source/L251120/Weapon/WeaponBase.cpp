// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "BaseDamageType.h"
#include "TimerManager.h"
#include "ProjectileBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;


}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::Reload()
{
	CurrentBulletCount = MaxBulletCount;
	UE_LOG(LogTemp, Warning, TEXT("Reload %d"), CurrentBulletCount);
}

void AWeaponBase::Fire()
{
	float CurrentTimeofShoot = GetWorld()->TimeSeconds - TimeofLastShoot;

	if (CurrentTimeofShoot < RefireRate)
	{
		return;
	}

	if (bFullAuto)
	{
		GetWorld()->GetTimerManager().SetTimer(RefireTimer, this, &AWeaponBase::Fire, RefireRate, false);
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());

	ensure(Character); //매크로로 캐릭터가 NULL 값이면 오류 띄어준다고 한다.
	//check(Character); //이건 에디터까지 죽어서 위치를 알려주는 메크로
	if (!Character)
	{
		return;
	}

	FTransform SpawnTransform = Mesh->GetSocketTransform(TEXT("Muzzle"));

	GetWorld()->SpawnActor<AProjectileBase>(ProjectileTemplate, SpawnTransform);

	APlayerController* PC = Cast<APlayerController>(Character->GetController());
	if (PC)
	{
		int32 SizeX = 0;
		int32 SizeY = 0;
		int32 CenterX = 0;
		int32 CenterY = 0;
		FVector WoirldDiretion;
		FVector WoirldLocation;
		FVector CameraLocation;
		FRotator CameraRotator;

		PC->GetViewportSize(SizeX, SizeY);

		CenterX = SizeX / 2;
		CenterY = SizeY / 2;

		PC->DeprojectScreenPositionToWorld((float)CenterX, (float)CenterY, WoirldLocation, WoirldDiretion);

		PC->GetPlayerViewPoint(CameraLocation, CameraRotator);

		FVector Start = CameraLocation;
		FVector End = CameraLocation + WoirldDiretion * 100000.f;

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		//ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
		//이것보단.. 그냥 BP 쓰는게 편하다고 한다..

		TArray<AActor*> IngnoreActors;
		IngnoreActors.Add(GetOwner());

		FHitResult HitResult;

		bool bResult = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			Start,
			End,
			ObjectTypes,
			true,
			IngnoreActors,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true
		);

		if (bResult)
		{
			//RPG 
			//UGameplayStatics::ApplyDamage(HitResult.GetActor(),
			//	10,
			//	PC,
			//	this,
			//	UBaseDamageType::StaticClass()
			//);

			////총쏘는 데미지
			UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),
				10,
				-HitResult.ImpactNormal,
				HitResult,
				PC,
				this,
				UBaseDamageType::StaticClass()
			);

			////범위 공격, 폭탄
			/*UGameplayStatics::ApplyRadialDamage(HitResult.GetActor(),
				10,
				HitResult.ImpactPoint,
				300.0f,
				UBaseDamageType::StaticClass(),
				IngnoreActors,
				this,
				PC,
				true
			);*/

			UGameplayStatics::PlaySound2D(GetWorld(), FireSoundCue);
			UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.GetActor()->GetName());
		}
	}

	CurrentBulletCount--;
	UE_LOG(LogTemp, Warning, TEXT("Fire %d"), CurrentBulletCount);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), FireSoundCue, GetActorLocation());
	TimeofLastShoot = GetWorld()->TimeSeconds;
}

void AWeaponBase::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(RefireTimer);
}

void AWeaponBase::FireProjectile()
{

}
