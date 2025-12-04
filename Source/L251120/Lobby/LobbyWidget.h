// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UButton;
class UEditableTextBox;
class UTextBlock;
class UScrollBox;

/**
 * 
 */
UCLASS()
class L251120_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ChatInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> ConnectionCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UTextBlock> LeftTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component", meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatScrollBox;


public:
	UFUNCTION()
	void Start();

	UFUNCTION()
	void ProcessOnCommite(const FText& Text, ETextCommit::Type CommitMethod);

	void ProcessOnChange(const FText& Text);

	UFUNCTION(BlueprintCallable)
	void UpdateLeftTime(int32 InLeftTime);

	UFUNCTION(BlueprintCallable)
	void UpdateConnectionCount(int32 InConnectionCount);

	void AddMessage(const FText& Message);
};
