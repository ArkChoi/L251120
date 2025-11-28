// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Zombie_AIC.generated.h"

/**
 * 
 */
UCLASS()
class L251120_API AZombie_AIC : public AAIController
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UAIPerceptionComponent> Perception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UBehaviorTree> RunBTAsset;

public:
	AZombie_AIC();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	void ProcessPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void ProcessActorPerceptionUpdated (AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void ProcessActorPerceptionForgetUpdated(AActor* Actor);

	UFUNCTION()
	void ProcessActorPerceptionInfoUpdated (const FActorPerceptionUpdateInfo& UpdateInfo);

};
