// Fill out your copyright notice in the Description page of Project Settings.


#include "LCAnimInstance.h"
#include "Gameframework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LMyCharacter.h"
#include "KismetAnimationLibrary.h"

void ULCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ALMyCharacter* Character = Cast<ALMyCharacter>(TryGetPawnOwner());//여기서 Try를 쓰는 이유는 각 따로 CPU 사용하다보니 한쪽만 죽고 다른 한쪽은 안죽었을수도 있다보니 Try로 한번 조건을 거치는 것이다.
	if (Character)
	{
		GroundSpeed = Character->GetCharacterMovement()->Velocity.Size2D();
		this->bIsRun = Character->bIsRun;
		//Direction = CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation()); //오류 나는거 확인해 보라고 남겨둔다..
		Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetCharacterMovement()->Velocity, Character->GetActorRotation());
		AimYaw = Character->GetAimOffset().Yaw;
		AimPitch = Character->GetAimOffset().Pitch;
		bAiming = Character->bAiming;
		bLeftLean = Character->bLeftLean;
		bRightLean = Character->bRightLean;
		bCrouching = Character->bCrouching;
		bIsFalling = Character->GetCharacterMovement()->IsFalling();

		float TargetLeanAngle = 0;
		if (bLeftLean)
		{
			TargetLeanAngle = -30.f;
		}
		else if (bRightLean)
		{
			TargetLeanAngle = 30.f;
		}
		else
		{
			TargetLeanAngle = 0;
		}
		CurrentLeanAngle = FMath::FInterpTo(CurrentLeanAngle, TargetLeanAngle, DeltaSeconds, 8.0f);

		WeaponState = Character->WeaponState;
	}
}

void ULCAnimInstance::AnimNotify_SkeletonNotify()
{
	UE_LOG(LogTemp, Warning, TEXT("SkeletonNotify"));
}
