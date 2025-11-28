// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckDistince.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Base/ZombieBase.h"

UBTTask_CheckDistince::UBTTask_CheckDistince()
{
	NodeName = TEXT("CheckDistince");
}

EBTNodeResult::Type UBTTask_CheckDistince::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	AZombieBase* Zombie = Cast<AZombieBase>(OwnerComp.GetAIOwner()->GetPawn());

	if (Player && Zombie)
	{
		FVector ZombieLocation = Zombie->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		float Distance = FVector::Distance(ZombieLocation, PlayerLocation);

		switch (TargetCondition)
		{
		case ECondition::LessThan:
			if (Distance > TargetDistance)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
			}
			break;
		case ECondition::GraterThan:
			if (Distance < TargetDistance)
			{
				Zombie->SetState(TargetState);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(GetSelectedBlackboardKey(), (uint8)TargetState);
			}
			break;
		default:
			break;
		}
	}

	return EBTNodeResult::Type();
}
