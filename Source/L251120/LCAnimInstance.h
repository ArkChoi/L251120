// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LCAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API ULCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float GroundSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	uint8 bIsRun : 1 = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float AimYaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	float AimPitch;

	UFUNCTION()
	void AnimNotify_SkeletonNotify();

};
