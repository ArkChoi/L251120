// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGS.h"
#include "Net/UnrealNetwork.h"

void ALoginGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALoginGS, AliveCount);
}

void ALoginGS::OnRep_AliveCount(const int32 InAliveCount)
{
	OnChangeAliveCount.ExecuteIfBound(AliveCount);
}
