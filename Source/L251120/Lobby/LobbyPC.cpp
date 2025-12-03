// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"

ALobbyPC::ALobbyPC()
{

}

void ALobbyPC::BeginPlay()
{
	Super::BeginPlay();

	if (LobbyWidgetClass)
	{
		if (IsLocalPlayerController()) //UE에서 남에 PC에 UE 붙이면 엔진이 쫒아낸다고 한다.
		{
			UE_LOG(LogTemp, Warning, TEXT("ALobbyPC::BeginPlay"));
			LobbyWidgetObject = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
			LobbyWidgetObject->AddToViewport();
		}
	}
}

void ALobbyPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ALobbyGS* GS = Cast<ALobbyGS>(UGameplayStatics::GetGameState(GetWorld()));

	if (GS && LobbyWidgetObject)
	{
		LobbyWidgetObject->UpdateLeftTime(GS->LeftTime);
	}

}
