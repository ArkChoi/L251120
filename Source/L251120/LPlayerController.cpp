// Fill out your copyright notice in the Description page of Project Settings.


#include "LPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "Login/LoginWidget.h"
//#include "Login/LoginGM.h"
//#include "Kismet/GameplayStatics.h"

ALPlayerController::ALPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_Asset(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (IMC_Asset.Succeeded())
	{
		InputMapping = IMC_Asset.Object;
	}
}

void ALPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	/*if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}*/
}

void ALPlayerController::OnUnPossess()
{
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(InputMapping);
			}
		}
	}
	Super::OnUnPossess();
}

void ALPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}

	if (LoginWidgetClass)
	{
		if (IsLocalPlayerController())
		{
			LoginWidgetObject = CreateWidget<ULoginWidget>(this, LoginWidgetClass);
			LoginWidgetObject->AddToViewport();
			LoginWidgetObject->SetOwningPlayer(this);
			LoginWidgetObject->UpDateHPBar(1.f);
		}
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}
