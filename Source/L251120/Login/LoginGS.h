// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "LoginGS.generated.h"


DECLARE_DELEGATE_OneParam(FOnChangeAliveCount, const int32);
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing = "OnRep_AliveCount")
	int32 AliveCount = 0;

	FOnChangeAliveCount OnChangeAliveCount;

};
