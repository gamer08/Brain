// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "MyObject.h"
#include "BrainGameMode.generated.h"

UCLASS(minimalapi)
class ABrainGameMode : public AGameMode
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UMyObject* _obj;
	
	void SetupGameModeWithCustomClasses();

public:
	ABrainGameMode();

	void BeginPlay() override;

	void CreatePauseMenu();
};



