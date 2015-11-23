// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLevelButtonWidget.h"
#include "Widgets/Menus/BrainLevelSelectionMenuWidget.h"

UBrainLevelButtonWidget::UBrainLevelButtonWidget()
: Super()
{
}

void UBrainLevelButtonWidget::OnClick()
{
	UTextBlock* text = Cast<UTextBlock>(GetChildAt(0));
	FString saveName = text->GetText().ToString();

	UBrainLevelSelectionMenuWidget* levelMenu = Cast<UBrainLevelSelectionMenuWidget>(GetOuter());
	levelMenu->LoadLevel(saveName);
}


