// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPC.generated.h"

class ULobbyWidget;
/**
 * 
 */
UCLASS()
class L251120_API ALobbyPC : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPC();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//자동으로 네트워크 통해 실행 하는 코드 생성
	UFUNCTION(Server, Reliable, WithValidation) //Reliable 도착 확인 , Unreliable 도착 미 확인
	void SendMessage(const FText& Message); //Network 던지는 코드 생성 (자동)
	bool SendMessage_Validate(const FText& Message); //WithValidation 키워드로 서버에서 클라이언트 확인
	void SendMessage_Implementation(const FText& Message); //구현

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(const FText& Message);
	void S2C_SendMessage_Implementation(const FText& Message);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<ULobbyWidget> LobbyWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<ULobbyWidget> LobbyWidgetObject;

};
