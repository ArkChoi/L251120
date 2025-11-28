// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "../LMyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Zombie/Zombie_AIC.h"

// Sets default values
AZombieBase::AZombieBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0, 0, -GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.f, 0));

}

// Called when the game starts or when spawned
void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//BT로 넘어감
}

float AZombieBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
		SpawnHitEffect(Event->HitInfo);
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

	if (CurrentHP <= 0)
	{
		SetState(EZombieState::Death);
		AZombie_AIC* AIC = Cast<AZombie_AIC>(GetController());
		if (AIC)
		{
			AIC->SetState(CurrentState);
		}
	}

	return 0.0f;
}

void AZombieBase::SpawnHitEffect(const FHitResult& Hit)
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

void AZombieBase::DoDead()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void AZombieBase::SetState(EZombieState NewState)
{
	CurrentState = NewState;

}

void AZombieBase::ChangeSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}
