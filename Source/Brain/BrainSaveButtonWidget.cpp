// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveButtonWidget.h"
#include "BrainSaveMenuWidget.h"

UBrainSaveButtonWidget::UBrainSaveButtonWidget()
: Super()
{
}

void UBrainSaveButtonWidget::OnClick()
{
	UTextBlock* text = Cast<UTextBlock>(GetChildAt(0));
	FString saveName = text->GetText().ToString();

	if (saveName.Equals("Nouvelle sauvegarde"))
		saveName.Empty();

	UBrainSaveMenuWidget* saveMenu = Cast<UBrainSaveMenuWidget>(GetOuter());
	saveMenu->Save(saveName);
}

