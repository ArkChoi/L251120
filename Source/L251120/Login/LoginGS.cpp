// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGS.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "LoginGM.h"

void ALoginGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALoginGS, AliveCount);
}

void ALoginGS::OnRep_AliveCount(const int32 InAliveCount)
{
	OnChangeAliveCount.ExecuteIfBound(AliveCount);

}

void ALoginGS::CountDownEndGame()
{
	if (EndTime > 0)
	{
		EndTime--;
		OnRep_EndTime();
	}
	else
	{
		ALoginGM* GM = Cast<ALoginGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			GM->EndGame();
		}
	}
}

void ALoginGS::OnRep_EndTime()
{
	OnChangeEndTime.Broadcast(EndTime);
}
