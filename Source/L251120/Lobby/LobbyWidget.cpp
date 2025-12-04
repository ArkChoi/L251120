// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"

void ULobbyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ULobbyWidget::Start);
	}
	if (ChatInput)
	{
		ChatInput->OnTextCommitted.AddDynamic(this, &ULobbyWidget::ProcessOnCommite);
		ChatInput->OnTextChanged.AddDynamic(this, &ULobbyWidget::ProcessOnChange);
	}

	ALobbyGS* GS = Cast<ALobbyGS>(UGameplayStatics::GetGameState((GetWorld())));
	if (GS)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bind"));
		GS->OnChangeLeftTime.AddDynamic(this, &ULobbyWidget::UpdateLeftTime);
		GS->OnChangeConnectionCount.AddDynamic(this, &ULobbyWidget::UpdateConnectionCount);
	}

}

void ULobbyWidget::Start()
{
	GetWorld()->ServerTravel(TEXT("InGame"));
}

void ULobbyWidget::ProcessOnCommite(const FText& Text, ETextCommit::Type CommitMethod)
{

}

void ULobbyWidget::ProcessOnChange(const FText& Text)
{
}

void ULobbyWidget::UpdateLeftTime(int32 InLeftTime)
{
	if (LeftTime)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Update"));
		FString Message = FString::Printf(TEXT("%d\'s late"), InLeftTime);
		LeftTime->SetText(FText::FromString(Message));
	}
}

void ULobbyWidget::UpdateConnectionCount(int32 InConnectionCount)
{
	if (ConnectionCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("Update"));
		FString Message = FString::Printf(TEXT("%d Connection"), InConnectionCount);
		ConnectionCount->SetText(FText::FromString(Message));
	}
}
