// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveMenuWidget.h"
#include "BrainGameInstance.h"
#include "BrainSaveButtonWidget.h"

void UBrainSaveMenuWidget::FillSavesList(UScrollBox* container)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		if (gameInstance)
			_saveFilesList = gameInstance->GetSaveManager()->GetSaveFilesName();

		//rajout d'une sauvegarde vide 

		UBrainSaveButtonWidget* btn = NewObject<UBrainSaveButtonWidget>(this);
		UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));

		text->SetText(FText::FromString("Nouvelle sauvegarde"));
		btn->AddChild(text);
		container->AddChild(btn);


		for (FString name : _saveFilesList)
		{
			UBrainSaveButtonWidget* btn = NewObject<UBrainSaveButtonWidget>(this);
			UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));

			text->SetText(FText::FromString(name));
			btn->AddChild(text);
			container->AddChild(btn);
		}
	}
}

void UBrainSaveMenuWidget::Save(FString saveName)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		bool isSaveSuccessfull = false;
		
		if (gameInstance)
			isSaveSuccessfull = gameInstance->GetSaveManager()->Save(saveName);

		if (isSaveSuccessfull)
			CloseOnSaveSuccessfull();
	}
}

