// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALPlayerController();

public:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

public:
	virtual void OnPossess(APawn* aPawn) override;
	void OnUnPossess() override;

};
