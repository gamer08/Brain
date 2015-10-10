// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "BrainHUDWidget.h"
#include "BrainHUD.generated.h"

UCLASS()
class ABrainHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABrainHUD();

	virtual void DrawHUD() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="test" )
	TSubclassOf<UBrainHUDWidget> _hudWidgetClass;

	void OnReceiveSelectedObjectActions(FObjectAction actions);

private:
	class UTexture2D* CrosshairTex;

	UPROPERTY()
	UBrainHUDWidget* _hudWidget;	

	void BeginPlay() override;
};