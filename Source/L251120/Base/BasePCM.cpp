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
		if (!Pawn->bIsIronSight)
		{
			CurrentFOV = FMath::FInterpTo(CurrentFOV, NormalFOV, GetWorld()->DeltaTimeSeconds, ZoomSpeed);
			SetFOV(CurrentFOV);
		}
		else
		{
			CurrentFOV = FMath::FInterpTo(CurrentFOV, IronsightFOV, GetWorld()->DeltaTimeSeconds, ZoomSpeed);
			SetFOV(CurrentFOV);
		}
	}
}