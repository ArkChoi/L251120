// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "../Base/ZombieBase.h"
#include "BTTask_CheckDistince.generated.h"

UENUM(BlueprintType)
enum class ECondition : uint8
{
	LessThan = 0 UMETA(DisplayName = "<"),
	GraterThan = 1 UMETA(DisplayName = ">"),
};
/**
 * 
 */
UCLASS()
class L251120_API UBTTask_CheckDistince : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckDistince();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
	ECondition TargetCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
	EZombieState TargetState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Condition")
	float TargetDistance;
};
