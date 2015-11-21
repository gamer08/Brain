// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLoadButtonWidget.h"
#include "Widgets/Menus/BrainLoadMenuWidget.h"

UBrainLoadButtonWidget::UBrainLoadButtonWidget()
: Super()
{
}

void UBrainLoadButtonWidget::OnClick()
{
	UTextBlock* text = Cast<UTextBlock>(GetChildAt(0));
	FString saveName = text->GetText().ToString();

	UBrainLoadMenuWidget* loadMenu = Cast<UBrainLoadMenuWidget>(GetOuter());
	loadMenu->LoadSave(saveName);
}


