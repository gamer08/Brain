// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "BrainGameMode.generated.h"

UCLASS(minimalapi)
class ABrainGameMode : public AGameMode
{
	GENERATED_BODY()

private:
	void SetupGameModeWithCustomClasses();

public:
	ABrainGameMode();

	void BeginPlay() override;

	void CreatePauseMenu();
};