// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Brain.h"
#include "BrainHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Blueprint/UserWidget.h"

ABrainHUD::ABrainHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}

void ABrainHUD::BeginPlay()
{
	
	_hudWidgetClass = LoadClass<UBrainHUDWidget>(nullptr, TEXT("/Game/FirstPerson/HUD/HUD.HUD_C"), nullptr, LOAD_None, nullptr);

	if (_hudWidgetClass)
	{
		_hudWidget = CreateWidget<UBrainHUDWidget>(GetWorld(), _hudWidgetClass);
		_hudWidget->AddToViewport();
	}

	Super::BeginPlay();
}

void ABrainHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D CrosshairDrawPosition( (Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
										   (Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)) );

	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void ABrainHUD::OnReceiveSelectedObjectActions(FObjectAction actions)
{
	_hudWidget->SetAvailableAction(actions);
}

void ABrainHUD::UpdateActionBar()
{
	_hudWidget->UpdateActionBar();
}