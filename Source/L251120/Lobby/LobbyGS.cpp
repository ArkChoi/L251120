// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "LobbyPC.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyWidget.h"
#include "LobbyGM.h"


void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, LeftTime);
	DOREPLIFETIME(ALobbyGS, ConnectionCount);
}

void ALobbyGS::OnRep_LeftTime()
{
	/*ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (PC && PC->LobbyWidgetObject)
	{
		PC->LobbyWidgetObject->UpdateLeftTime(LeftTime);
	}*/

	OnChangeLeftTime.Broadcast(LeftTime);
}

void ALobbyGS::OnRep_ConnectionCount()
{
	OnChangeConnectionCount.Broadcast(ConnectionCount);
}

void ALobbyGS::CountDownLeftTime()
{
	//Server
	if (LeftTime > 0)
	{
		LeftTime--;
		OnRep_LeftTime();
	}
	else
	{
		ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GM)
		{
			GM->StartGame();
		}
	}
}

void ALobbyGS::BeginPlay()
{
	Super::BeginPlay();
}
