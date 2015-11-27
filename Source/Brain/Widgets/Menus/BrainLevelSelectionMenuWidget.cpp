// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLevelSelectionMenuWidget.h"
#include "Widgets/Others/BrainLevelButtonWidget.h"


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

		USlateWidgetStyleAsset* slateStyle = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/FirstPerson/Menus/BrainButtonStyle.BrainButtonStyle"),nullptr,LOAD_None,nullptr);
		const FButtonStyle* btnStyle = slateStyle->GetStyle<FButtonStyle>();
		FLinearColor color = FLinearColor(1,0.255,0,1);
		FSlateColor slateColor = FSlateColor(color);

		for (FString name : _levelList)
		{
			UBrainLevelButtonWidget* btn = NewObject<UBrainLevelButtonWidget>(this);
			btn->WidgetStyle = *btnStyle;
			
			UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));
			text->ColorAndOpacity = slateColor;
			
			name.RemoveFromEnd(".umap");

			text->SetText(FText::FromString(name));
			btn->AddChild(text);
			container->AddChild(btn);
		}

		TArray<UPanelSlot*> slots = container->GetSlots();
		for (UPanelSlot* slot : slots)
		{
			if (UScrollBoxSlot* sSlot = Cast<UScrollBoxSlot>(slot))
				sSlot->SetPadding(FMargin(0, 0, 0, 5.0f));
		}
	}
}

void UBrainLevelSelectionMenuWidget::LoadLevel(FString name)
{
	UWorld* world = GetWorld();
	if (world)
		UGameplayStatics::OpenLevel(world,FName(*name));
}



