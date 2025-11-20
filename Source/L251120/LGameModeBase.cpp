// Fill out your copyright notice in the Description page of Project Settings.


#include "LGameModeBase.h"
#include "LMyCharacter.h"
#include "LPlayerController.h"

ALGameModeBase::ALGameModeBase()
{
	DefaultPawnClass = ALMyCharacter::StaticClass();
	PlayerControllerClass = ALPlayerController::StaticClass();
}
