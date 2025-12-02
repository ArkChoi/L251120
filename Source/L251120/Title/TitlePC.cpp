// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePC.h"
#include "TitleWidget.h"

void ATitlePC::BeginPlay()
{
	Super::BeginPlay();

	//include 식으로 BP 불러오기
	//1. 경로 설정
	FSoftClassPath TitleWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Title/WBP_TitleWidget.WBP_TitleWidget_C'"));

	//2. include "Path" -> Class 정의 (생성X)
	UClass* WidgetClass = TitleWidgetClass.TryLoadClass<UTitleWidget>();

	if (WidgetClass)
	{
		//3. new Class
		TitleWidgetObject = CreateWidget<UTitleWidget>(this, WidgetClass);
		if (TitleWidgetObject)
		{
			TitleWidgetObject->AddToViewport();
		}
	}
}

void ATitlePC::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}
