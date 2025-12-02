// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitlePC.generated.h"

class UTitleWidget;

/**
 * 
 */
UCLASS()
class L251120_API ATitlePC : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override; //위치상 컴포넌트 추가 직후라고 한다. + 네트워크 이전 , BeginPlay는 네트워크 이후 , 초기화 순서 중요

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UTitleWidget> TitleWidgetObject;
};
