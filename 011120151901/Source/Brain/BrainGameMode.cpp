// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Brain.h"
#include "BrainGameMode.h"
#include "BrainHUD.h"
#include "BrainCharacter.h"
#include "BrainPlayerController.h"
#include "BrainMainMenuWidget.h"
#include "BrainLoadMenuWidget.h"

ABrainGameMode::ABrainGameMode()
: Super()
{
	if (UWorld* world = GetWorld())
	{
		if (world->GetName().Equals(FString("MainMenu")))
		{
			DefaultPawnClass = APawn::StaticClass();
			PlayerControllerClass = APlayerController::StaticClass();
		}
		else
			SetupGameModeWithCustomClasses();
	}
	else
		SetupGameModeWithCustomClasses();
}

void ABrainGameMode::SetupGameModeWithCustomClasses()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BrainCharacter"));
	
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = ABrainPlayerController::StaticClass();
	HUDClass = ABrainHUD::StaticClass();
}

void ABrainGameMode::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (world && world->GetName().Equals(FString("MainMenu")))
	{
		APlayerController* pc = world->GetFirstPlayerController();
		pc->bShowMouseCursor = true;
		pc->bEnableClickEvents = true;
		pc->bEnableMouseOverEvents = true;
		DisableInput(pc);
		
		TSubclassOf<UBrainMainMenuWidget> mainMenuWidgetClass = LoadClass<UBrainMainMenuWidget>(nullptr, TEXT("/Game/FirstPerson/Menus/MainMenu.MainMenu_C"), nullptr, LOAD_None, nullptr);

		if (mainMenuWidgetClass)
		{
			UBrainMainMenuWidget* mainMenuWidget = CreateWidget<UBrainMainMenuWidget>(GetWorld(), mainMenuWidgetClass);
			mainMenuWidget->AddToViewport();
		}
	}
}



