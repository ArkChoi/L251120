// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "LoginGS.generated.h"


DECLARE_DELEGATE_OneParam(FOnChangeAliveCount, const int32);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeEndTime, const int32, InEndTime);

/**
 * 
 */
UCLASS()
class L251120_API ALoginGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_AliveCount(const int32 InAliveCount);

	void CountDownEndGame();

	UFUNCTION()
	void OnRep_EndTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing = "OnRep_AliveCount")
	int32 AliveCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing = "OnRep_EndTime")
	int32 EndTime = 10;

	FOnChangeAliveCount OnChangeAliveCount;

	FOnChangeEndTime OnChangeEndTime;

};
