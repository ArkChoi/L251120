// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_Startend.h"

FString UAnimNotifyState_Startend::GetNotifyName_Implementation() const
{
	return TEXT("Startend");
}

void UAnimNotifyState_Startend::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UE_LOG(LogTemp, Warning, TEXT("NotifyBegin"));
}

void UAnimNotifyState_Startend::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	UE_LOG(LogTemp, Warning, TEXT("NotifyTick"));
}

void UAnimNotifyState_Startend::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Warning, TEXT("NotifyEnd"));
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}