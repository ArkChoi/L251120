// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAnimInstance.h"
#include "../Base/ZombieBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UZombieAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AZombieBase* Zombie = Cast<AZombieBase>(TryGetPawnOwner());
	if (Zombie)
	{
		GroundSpeed = Zombie->GetCharacterMovement()->Velocity.Size2D();
		CurrentState = Zombie->CurrentState;
	}
}
