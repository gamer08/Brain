// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLevelSelectionMenuWidget.h"
#include "BrainLevelButtonWidget.h"


void UBrainLevelSelectionMenuWidget::FillLevelsList(UScrollBox* container)
{
	UWorld* world = GetWorld();
	if (world)
	{
		FString path = FPaths::GameContentDir();
		path += "/FirstPerson/Maps";

		FString pathNFilter = path + "/" + "*.umap";
		IFileManager::Get().FindFiles(_levelList, *pathNFilter, true, true);

		FString mainMenuMap = FString("MainMenu.umap");
		_levelList.Remove(mainMenuMap);

		for (FString name : _levelList)
		{
			UBrainLevelButtonWidget* btn = NewObject<UBrainLevelButtonWidget>(this);
			UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));

			name.RemoveFromEnd(".umap");

			text->SetText(FText::FromString(name));
			btn->AddChild(text);
			container->AddChild(btn);
		}
	}
}

void UBrainLevelSelectionMenuWidget::LoadLevel(FString name)
{
	UWorld* world = GetWorld();
	if (world)
		UGameplayStatics::OpenLevel(world,FName(*name));
}



