// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Look.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_Look::UBTService_Look()
{
	NodeName = TEXT("LookPlayer");
}

void UBTService_Look::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Target)
	{
		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Target->GetActorLocation();

		FRotator TargetPoint = UKismetMathLibrary::FindLookAtRotation(ZombieLocation, PlayerLocation);
		OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(TargetPoint);
	}
}
