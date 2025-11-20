// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetpSound.h"

FString UAnimNotify_SetpSound::GetNotifyName_Implementation() const
{
	return TEXT("StepSound");
}

void UAnimNotify_SetpSound::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	UE_LOG(LogTemp, Warning, TEXT("Left"));
}