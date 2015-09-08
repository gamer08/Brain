// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "BrainHUD.generated.h"

UCLASS()
class ABrainHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABrainHUD();

	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;

};