// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGM.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API ALoginGM : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay()override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	void CheckAliveCount();

public:
	FTimerHandle GameEndTimerHandle;
};
