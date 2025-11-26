// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePCM.h"
#include "../LMyCharacter.h"


ABasePCM::ABasePCM()
{

}

void ABasePCM::UpdateCamera(float DeltaTime)
{
	Super::UpdateCamera(DeltaTime);

	ALMyCharacter* Pawn = Cast<ALMyCharacter>(GetOwningPlayerController()->GetPawn());

	if (Pawn)
	{
		if (Pawn->bIsIronSight)
		{
			SetFOV(60.f);
		}
		else
		{
			SetFOV(90.f);
		}
	}
}