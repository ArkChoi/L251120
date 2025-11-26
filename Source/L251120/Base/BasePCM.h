// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "BasePCM.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API ABasePCM : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ABasePCM();

	virtual void UpdateCamera(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float NormalFOV = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float IronsightFOV = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float CurrentFOV = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float ZoomSpeed = 5.f;
};
