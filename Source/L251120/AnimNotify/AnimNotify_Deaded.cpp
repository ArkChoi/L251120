// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Deaded.h"
#include "../LMyCharacter.h"

FString UAnimNotify_Deaded::GetNotifyName_Implementation() const
{
	return TEXT("Deaded");
}

void UAnimNotify_Deaded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ALMyCharacter* BaseCharacter = Cast<ALMyCharacter>(MeshComp->GetOwner());
	if (BaseCharacter)
	{
		BaseCharacter->DoDead();
	}
}