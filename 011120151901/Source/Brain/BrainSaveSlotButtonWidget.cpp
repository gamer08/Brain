// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveSlotButtonWidget.h"
#include "BrainLoadMenuWidget.h"


UBrainSaveSlotButtonWidget::UBrainSaveSlotButtonWidget()
: Super()
{
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		OnClicked.AddDynamic(this, &UBrainSaveSlotButtonWidget::OnClick);

		//Bind function
		load.AddDynamic(this, &UBrainSaveSlotButtonWidget::LoadGameFile);
	}
}

void UBrainSaveSlotButtonWidget::OnClick()
{
	UTextBlock* text = Cast<UTextBlock>(GetChildAt(0));
	FString saveName = text->GetText().ToString();

	UBrainLoadMenuWidget* loadMenu = Cast<UBrainLoadMenuWidget>(GetOuter());
	loadMenu->LoadSave(saveName);	
}

void UBrainSaveSlotButtonWidget::LoadGameFile(FString name)
{
	/** load stuff here **/
}


