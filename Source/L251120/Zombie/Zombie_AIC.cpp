// Fill out your copyright notice in the Description page of Project Settings.


#include "Zombie_AIC.h"
#include "perception/AIPerceptionComponent.h"
#include "perception/AISenseConfig_Sight.h"
#include "../LMyCharacter.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Base/ZombieBase.h"

AZombie_AIC::AZombie_AIC()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("StimuliSource"));

	//BP로 잘 구현되어 있으니 앞으로는 그거 쓰라고..
	UAISenseConfig_Sight * Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	Sight->SightRadius = 300.f;
	Sight->LoseSightRadius = 400.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());
}

void AZombie_AIC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (RunBTAsset)
	{
		RunBehaviorTree(RunBTAsset);
	}

	//Perception->OnPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessPerceptionUpdated);
	Perception->OnTargetPerceptionForgotten.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionForgetUpdated);
	//Perception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionInfoUpdated);
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &AZombie_AIC::ProcessActorPerceptionUpdated);

	SetGenericTeamId(3);
}

void AZombie_AIC::OnUnPossess()
{


	Super::OnUnPossess();
}

//void AZombie_AIC::ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
//{
//	for (auto Actor : UpdatedActors)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("ProcessPerceptionUpdated %s"), *Actor->GetName());
//	}
//}

void AZombie_AIC::ProcessActorPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionUpdated %s %s"), *Actor->GetName(), *Stimulus.Type.Name.ToString());

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			ALMyCharacter* Player = Cast<ALMyCharacter>(Actor);
			AZombieBase* Zombie = Cast<AZombieBase>(GetPawn());

			if (Player && Zombie)
			{
				Blackboard->SetValueAsObject(TEXT("Target"), Player);
				Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(EZombieState::Chase));
				Zombie->SetState(EZombieState::Chase);
				Zombie->ChangeSpeed(300.f);
			}
		}
		else
		{
			ALMyCharacter* Player = Cast<ALMyCharacter>(Actor);
			AZombieBase* Zombie = Cast<AZombieBase>(GetPawn());

			if (Player && Zombie)
			{
				Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
				Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(EZombieState::Normal));
				Zombie->SetState(EZombieState::Normal);
				Zombie->ChangeSpeed(60.f);
			}
		}
	}

}

void AZombie_AIC::ProcessActorPerceptionForgetUpdated(AActor* Actor)
{
	//UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionForgetUpdated %s"), *Actor->GetName());

	ALMyCharacter* Player = Cast<ALMyCharacter>(Actor);
	AZombieBase* Zombie = Cast<AZombieBase>(GetPawn());

	if (Player && Zombie)
	{
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
		Blackboard->SetValueAsEnum(TEXT("CurrentState"), (uint8)(EZombieState::Normal));
		Zombie->SetState(EZombieState::Normal);
		Zombie->ChangeSpeed(60.f);
	}

}

//void AZombie_AIC::ProcessActorPerceptionInfoUpdated(const FActorPerceptionUpdateInfo& UpdateInfo)
//{
//	UE_LOG(LogTemp, Warning, TEXT("ProcessActorPerceptionForgetUpdated %s"), *UpdateInfo.Target->GetName());
//}
