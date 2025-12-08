// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGM.h"
#include "LoginGS.h"
#include "../LMyCharacter.h"

void ALoginGM::BeginPlay()
{
	Super::BeginPlay();

	CheckAliveCount();
}

void ALoginGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	CheckAliveCount();

}

void ALoginGM::Logout(AController* Exiting)
{
	CheckAliveCount();

	Super::Logout(Exiting);
}

void ALoginGM::CheckAliveCount()
{
	ALoginGS* GS = GetGameState<ALoginGS>();
	if (GS)
	{
		int32 TempCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			ALMyCharacter* Pawn = Cast<ALMyCharacter>((*Iter)->GetPawn());
			if (Pawn)
			{
				if (!Pawn->bIsDead)
				{
					TempCount++;
				}
			}
		}

		GS->AliveCount = TempCount;
		GS->OnRep_AliveCount(GS->AliveCount);

	}
}