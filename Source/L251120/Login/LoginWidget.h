// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class L251120_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized()override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> AliveCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> GameEndText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> CountTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UProgressBar> HPBar;

public:
	UFUNCTION()
	void UpDateAliveCount(int32 InAliveCount);

	UFUNCTION(BlueprintCallable)
	void UpDateHPBar(float InHP);

	UFUNCTION(BlueprintCallable)
	void UpdateEndTime(int32 InEndTime);

};
