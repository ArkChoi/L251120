// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "LoginGS.h"
#include "Kismet/GameplayStatics.h"
#include "../LMyCharacter.h"
#include "../Network/NetworkUtil.h"
#include "LoginGM.h"

void ULoginWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ALoginGS* GS = Cast<ALoginGS>(UGameplayStatics::GetGameState((GetWorld())));
	if (GS)
	{
		GS->OnChangeAliveCount.BindUObject(this, &ULoginWidget::UpDateAliveCount);
		GS->OnChangeEndTime.AddDynamic(this, &ULoginWidget::UpdateEndTime);
	}

	ALMyCharacter* Player = Cast<ALMyCharacter>(GetOwningPlayer()->GetPawn());
	if (Player)
	{
		Player->OnChangeHP.AddDynamic(this, &ULoginWidget::UpDateHPBar);
		Player->OnRep_CurrentHP(Player->CurrentHP / Player->MaxHP);
	}

	ALoginGM* GM = Cast<ALoginGM>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->CheckAliveCount();
	}

	if (CountTime)
	{
		CountTime->SetVisibility(ESlateVisibility::Hidden);
	}
	if (GameEndText)
	{
		GameEndText->SetVisibility(ESlateVisibility::Hidden);
	}

}

void ULoginWidget::UpDateAliveCount(int32 InAliveCount)
{
	if (AliveCount)
	{
		FString Message = FString::Printf(TEXT("%d : 생존"), InAliveCount);
		AliveCount->SetText(FText::FromString(Message));
	}
}

void ULoginWidget::UpDateHPBar(float InHP)
{
	if (HPBar)
	{
		HPBar->SetPercent(InHP);
	}
}

void ULoginWidget::UpdateEndTime(int32 InEndTime)
{
	if (CountTime)
	{
		CountTime->SetVisibility(ESlateVisibility::Visible);
	}
	if (GameEndText)
	{
		GameEndText->SetVisibility(ESlateVisibility::Visible);
	}


	if (CountTime)
	{
		FString Message = FString::Printf(TEXT("%d"), InEndTime);
		CountTime->SetText(FText::FromString(Message));
	}
}
