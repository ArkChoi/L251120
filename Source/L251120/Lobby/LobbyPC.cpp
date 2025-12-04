// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPC.h"
#include "LobbyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"
#include "LobbyGM.h"

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

			//Listen Sever만 실행되게 만든 것.. UI 생성 문제 때문에
			ALobbyGM* GM = Cast<ALobbyGM>(UGameplayStatics::GetGameMode(GetWorld()));
			if (GM)
			{
				GM->CheckConnectionCount();
			}
		}
	}
}

void ALobbyPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

bool ALobbyPC::SendMessage_Validate(const FText& Message)
{
	return true;
}

void ALobbyPC::SendMessage_Implementation(const FText& Message)
{
	for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		ALobbyPC* PC = Cast<ALobbyPC>(*Iter);
		if (PC)
		{
			PC->S2C_SendMessage(Message);
		}
	}
}

void ALobbyPC::S2C_SendMessage_Implementation(const FText& Message)
{
	if (LobbyWidgetObject)
	{
		LobbyWidgetObject->AddMessage(Message);
	}
}
