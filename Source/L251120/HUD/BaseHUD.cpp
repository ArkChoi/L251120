// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "Engine/Canvas.h"
#include "../LMyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	int32 UnitX = Canvas->SizeX / 100;
	int32 UnitY = Canvas->SizeY / 100;
	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;
	int32 DrawSize = 2;

	ALMyCharacter* TempCharacter = Cast<ALMyCharacter>(GetOwningPlayerController()->GetPawn());
	if (TempCharacter)
	{
		float GroundSpeed = TempCharacter->GetCharacterMovement()->Velocity.Size2D();
		if (GroundSpeed > 0 && TempCharacter->bIsRun)
		{
			DrawSize = 4;
		}
		else if (GroundSpeed > 0)
		{
			DrawSize = 3;
		}
		else
		{
			DrawSize = 2;
		}
	}

	Draw2DLine(CenterX - (UnitX * DrawSize),
		CenterY,
		CenterX - (UnitX * (DrawSize - 2)),
		CenterY,
		FColor::Red);

	Draw2DLine(CenterX + (UnitX * DrawSize),
		CenterY,
		CenterX + (UnitX * (DrawSize - 2)),
		CenterY,
		FColor::Red);

	Draw2DLine(CenterX,
		CenterY - (UnitX * DrawSize),
		CenterX,
		CenterY - (UnitX * (DrawSize - 2)),
		FColor::Red);

	Draw2DLine(CenterX,
		CenterY + (UnitX * DrawSize),
		CenterX,
		CenterY + (UnitX * (DrawSize - 2)),
		FColor::Red);
}
