// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Brain.h"
#include "BrainGameMode.h"
#include "BrainHUD.h"
#include "BrainCharacter.h"
#include "BrainPlayerController.h"

ABrainGameMode::ABrainGameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BrainCharacter"));
	
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = ABrainPlayerController::StaticClass();
	HUDClass = ABrainHUD::StaticClass();
}
