// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGS.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API ALobbyGS : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; //Replicated 키워드 쓰려면 꼭 재정의 해줘야함

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	int32 LeftTime = 60;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", Replicated)
	int32 ConnectionCount = 0;

};
