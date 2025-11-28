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
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (Player)
	{
		FVector ZombieLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();

		FRotator TargetPoint = UKismetMathLibrary::FindLookAtRotation(ZombieLocation, PlayerLocation);

		TargetPoint.Pitch = 0;

		FRotator TargetRotation = FMath::RInterpTo(
			OwnerComp.GetAIOwner()->GetPawn()->GetActorRotation(),
			TargetPoint,
			DeltaSeconds,
			15.f
			);

		OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(TargetRotation);
	}
}
