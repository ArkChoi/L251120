// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_Look.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API UBTService_Look : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_Look();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
