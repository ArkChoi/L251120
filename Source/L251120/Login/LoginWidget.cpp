// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "LoginGS.h"
#include "Kismet/GameplayStatics.h"
#include "../LMyCharacter.h"
#include "../Network/NetworkUtil.h"

void ULoginWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ALoginGS* GS = Cast<ALoginGS>(UGameplayStatics::GetGameState((GetWorld())));
	if (GS)
	{
		GS->OnChangeAliveCount.BindUObject(this, &ULoginWidget::UpDateAliveCount);
	}

	ALMyCharacter* Player = Cast<ALMyCharacter>(GetOwningPlayer()->GetPawn());
	if (Player)
	{
		Player->OnChangeHP.AddDynamic(this, &ULoginWidget::UpDateHPBar);
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
