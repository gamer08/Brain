// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLoadMenuWidget.h"
#include "BrainGameInstance.h"
#include "BrainSaveSlotButtonWidget.h"

void UBrainLoadMenuWidget::FillSavesList(UScrollBox* container)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		if (gameInstance)
			_saveFilesList = gameInstance->GetSaveManager()->GetSaveFilesName();

		for (FString name : _saveFilesList)
		{
			UBrainSaveSlotButtonWidget* btn = NewObject<UBrainSaveSlotButtonWidget>(this);
			UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));

			text->SetText(FText::FromString(name));
			btn->AddChild(text);
			container->AddChild(btn);
		}
	}
}

void UBrainLoadMenuWidget::LoadSave(FString saveToLoad)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		if (gameInstance)
			gameInstance->GetSaveManager()->Load(saveToLoad);
	}
}
