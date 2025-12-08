// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGM.h"
#include "LoginGS.h"
#include "../LMyCharacter.h"

void ALoginGM::BeginPlay()
{
	Super::BeginPlay();
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
		int32 PCCount = 0;
		int32 TempCount = 0;
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; Iter++)
		{
			PCCount++;
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

		if (PCCount>=2 && TempCount==1)
		{
			UE_LOG(LogTemp, Warning, TEXT("End Timer"));
			GetWorld()->GetTimerManager().SetTimer(
				GameEndTimerHandle,
				FTimerDelegate::CreateLambda([this]() //lambda ÇÔ¼ö
					{
						ALoginGS* GS = GetGameState<ALoginGS>();
						if (GS)
						{
							GS->CountDownEndGame();
						}
					}),
				1.0f,
				true,
				0.f);
		}

	}
}

void ALoginGM::EndGame()
{
	GetWorld()->GetTimerManager().ClearTimer(GameEndTimerHandle);
	
	GetWorld()->ServerTravel(TEXT("Lvl_Lobby"));
}
