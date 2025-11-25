// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "Engine/Canvas.h"
#include "GameFramework/Character.h"
//#include "../LMyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

void ABaseHUD::DrawHUD()
{
	Super::DrawHUD();

	int32 UnitX = Canvas->SizeX / 100;
	int32 UnitY = Canvas->SizeY / 100;
	int32 CenterX = Canvas->SizeX / 2;
	int32 CenterY = Canvas->SizeY / 2;
	int32 DrawSize = 2;

	float CurrentSpeed = 0.f;
	float MaxSpeed = 0.f;
	float GapRatio = 0.f;

	int32 GapX = UnitX;
	int32 GapY = UnitY;

	float DeltaSeconds = GetWorld()->GetDeltaSeconds();

	ACharacter* Pawn = Cast<ACharacter>(GetOwningPawn());
	if (Pawn)
	{
		CurrentSpeed = Pawn->GetCharacterMovement()->Velocity.Size2D();
		MaxSpeed = Pawn->GetCharacterMovement()->GetMaxSpeed();
		GapRatio = CurrentSpeed / MaxSpeed;

		/*if (GroundSpeed > 0 && Pawn->bIsRun)
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
		}*/
	}

	//ChangeSize = FMath::FInterpTo(ChangeSize, (float)DrawSize, DeltaSeconds, 1.f);

	GapX = (int32)((float)GapX * GapRatio);
	GapY = (int32)((float)GapY * GapRatio);

	Draw2DLine(CenterX - (UnitX * DrawSize) - GapX,
		CenterY,
		CenterX - GapX,
		CenterY,
		FColor::Red);

	Draw2DLine(CenterX + GapX,
		CenterY,
		CenterX + (UnitX * DrawSize) + GapX,
		CenterY,
		FColor::Red);

	Draw2DLine(CenterX,
		CenterY - GapX,
		CenterX,
		CenterY - (UnitX * DrawSize) - GapX,
		FColor::Red);

	Draw2DLine(CenterX,
		CenterY + GapX,
		CenterX,
		CenterY +(UnitX * DrawSize) + GapX,
		FColor::Red);
}
