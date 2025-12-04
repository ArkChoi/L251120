// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeLeftTime, const int32, InLeftTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeConnectionCount, const int32, InConnectionCount);

/**
 * 
 */
UCLASS()
class L251120_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; //Replicated 키워드 쓰려면 꼭 재정의 해줘야함

	UFUNCTION()
	void OnRep_LeftTime();

	UFUNCTION()
	void OnRep_ConnectionCount();

	void CountDownLeftTime();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing="OnRep_LeftTime")
	int32 LeftTime = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", ReplicatedUsing="OnRep_ConnectionCount")
	int32 ConnectionCount = 0;

	FOnChangeLeftTime OnChangeLeftTime;

	FOnChangeConnectionCount OnChangeConnectionCount;

	virtual void BeginPlay() override;
};
