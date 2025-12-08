// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "BaseDamageType.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(10, 10, 10));
	//Simulation Generated Hit Event
	Box->GetBodyInstance()->bNotifyRigidBodyCollision = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 8000.0f;
	Movement->InitialSpeed = 8000.0f;

	bReplicates = true;
	SetReplicateMovement(true);
	bNetLoadOnClient = true;
	bNetUseOwnerRelevancy = true;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	//OnActorBeginOverlap.AddDynamic(this, &AProjectileBase::ProcessBeginOverlap);
	Box->OnComponentHit.AddDynamic(this, &AProjectileBase::ProcessComponentHit);
	
	SetLifeSpan(5.0f);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::ProcessBeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{

	/*ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);
	if (HitCharacter)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BloodEffect,
			HitResult.ImpactPoint,
			HitResult.ImpactNormal.Rotation()
		);
	}*/

	//RPG 
//UGameplayStatics::ApplyDamage(HitResult.GetActor(),
//	50,
//	PC,
//	this,
//	UBaseDamageType::StaticClass()
//);

//√—ΩÓ¥¬ µ•πÃ¡ˆ
	//UGameplayStatics::ApplyPointDamage(HitResult.GetActor(),
	//	10,
	//	-HitResult.ImpactNormal,
	//	HitResult,
	//	PC,
	//	this,
	//	UBaseDamageType::StaticClass()
	//);

	////π¸¿ß ∞¯∞›, ∆¯≈∫
	//UGameplayStatics::ApplyRadialDamage(HitResult.GetActor(),
	//	10,
	//	HitResult.ImpactPoint,
	//	300.0f,
	//	UBaseDamageType::StaticClass(),
	//	IngnoreActors,
	//	this,
	//	PC,
	//	true
	//);
	Destroy();
}

void AProjectileBase::ProcessComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SpawnHitEffect(Hit);

	//if (GetLocalRole() == ENetRole::ROLE_Authority)
	//{
	//	NET_LOG(TEXT("Bullet ROLE_Authority"));
	//}
	//else if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	//{
	//	NET_LOG(TEXT("Bullet ROLE_AutonomousProxy"));
	//}
	//else if (GetLocalRole() == ENetRole::ROLE_SimulatedProxy)
	//{
	//	NET_LOG(TEXT("Bullet ROLE_SimulatedProxy"));
	//}

	//if (GetRemoteRole() == ENetRole::ROLE_Authority)
	//{
	//	NET_LOG(TEXT("Bullet Remote ROLE_Authority"));
	//}
	//else if (GetRemoteRole() == ENetRole::ROLE_AutonomousProxy)
	//{
	//	NET_LOG(TEXT("Bullet Remote ROLE_AutonomousProxy"));
	//}
	//else if (GetRemoteRole() == ENetRole::ROLE_SimulatedProxy)
	//{
	//	NET_LOG(TEXT("Bullet Remote ROLE_SimulatedProxy"));
	//}

	//

	//if (GetOwner())
	//{
	//	NET_LOG(FString::Printf(TEXT("Bullet Owner %s"), *GetOwner()->GetName()));
	//}
	//else
	//{
	//	NET_LOG(TEXT("Bullet No Owner"));
	//}

	//if (GetOwner()->GetOwner())
	//{
	//	NET_LOG(FString::Printf(TEXT("Gun Owner %s"), *GetOwner()->GetOwner()->GetName()));
	//}
	//else
	//{
	//	NET_LOG(TEXT("Gun No Owner"));
	//}

	//if (GetOwner()->GetOwner()->GetOwner())
	//{
	//	NET_LOG(FString::Printf(TEXT("Pawn Owner %s"), *GetOwner()->GetOwner()->GetOwner()->GetName()));
	//}
	//else
	//{
	//	NET_LOG(TEXT("Pawn No Owner"));
	//}

	if (!HasAuthority())
	{
		//º≠πˆ∞° æ∆¥œ∏È √—æÀ¿« ¡÷¿Œ¿Ã æ¯¥Ÿ.
		return;
	}

	APawn* Pawn = Cast<APawn>(GetOwner()->GetOwner());

	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %s"), *OtherActor->GetName(), *OtherComp->GetName());

		//√—ΩÓ¥¬ µ•πÃ¡ˆ
		UGameplayStatics::ApplyPointDamage(Hit.GetActor(),
			Damage,
			-Hit.ImpactNormal,
			Hit,
			Pawn->GetController(),
			this,
			UBaseDamageType::StaticClass()
		);
	}
}

void AProjectileBase::SpawnHitEffect(const FHitResult& Hit)
{
	if (Decal)
	{
		UDecalComponent* MadeDecal = UGameplayStatics::SpawnDecalAtLocation(
			GetWorld(),
			Decal,
			FVector(5, 5, 5),
			Hit.ImpactPoint,
			Hit.ImpactNormal.Rotation(),
			5.f
		);
		if (MadeDecal)
		{
			MadeDecal->SetFadeScreenSize(0.0005f);
		}
	}
}
