// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyGS.h"
#include "LobbyPC.h"
#include "../Title/DataGameInstanceSubsystem.h"

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
	GetWorld()->ServerTravel(TEXT("Lvl_InGame"));
	GetWorld()->GetTimerManager().ClearTimer(LeftTimerHandle);
}

void ULobbyWidget::ProcessOnCommite(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		case ETextCommit::Default:
			break;
		case ETextCommit::OnEnter:
		{
			ALobbyPC* PC = Cast<ALobbyPC>(GetOwningPlayer());
			if (PC)
			{
				UGameInstance* GI = UGameplayStatics::GetGameInstance(GetWorld());
				if (GI)
				{
					UDataGameInstanceSubsystem* MySubsystem = GI->GetSubsystem<UDataGameInstanceSubsystem>();
					//MySubsystem->UserID
					FString Temp = FString::Printf(TEXT("%s : %s"), *MySubsystem->UserID, *Text.ToString());

					//Local PC Call -> Server PC execute
					PC->SendMessage(FText::FromString(Temp));
					ChatInput->SetText(FText::FromString(""));
				}
			}
		}
			break;
		case ETextCommit::OnUserMovedFocus:
			break;
		case ETextCommit::OnCleared:
		{
			ChatInput->SetUserFocus(GetOwningPlayer());
		}
			break;
		default:
			break;
	}
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

void ULobbyWidget::AddMessage(const FText& Message)
{
	if (ChatScrollBox)
	{
		URichTextBlock* NewMessageBlock = NewObject<URichTextBlock>(ChatScrollBox);
		if (NewMessageBlock)
		{
			NewMessageBlock->SetText(Message);
			if (ChatTextStyle)
			{
				NewMessageBlock->SetTextStyleSet(ChatTextStyle);
			}
			/*FSlateFontInfo FontInfo = NewMessageBlock->GetFont();
			FontInfo.Size = 32;
			
			NewMessageBlock->SetFont(FontInfo);
			NewMessageBlock->SetColorAndOpacity(FSlateColor(FLinearColor(0, 0, 0)));*/

			ChatScrollBox->AddChild(NewMessageBlock);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

void ULobbyWidget::ShowStartButton()
{
	if (StartButton)
	{
		StartButton->SetVisibility(ESlateVisibility::Visible);
	}
}
