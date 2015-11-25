// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainLoadMenuWidget.h"
#include "BrainGameInstance.h"
#include "Widgets/Others/BrainLoadButtonWidget.h"

void UBrainLoadMenuWidget::FillSavesList(UScrollBox* container)
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		if (gameInstance)
			_saveFilesList = gameInstance->GetSaveManager()->GetSaveFilesName();

		USlateWidgetStyleAsset* slateStyle = LoadObject<USlateWidgetStyleAsset>(nullptr, TEXT("/Game/FirstPerson/Menus/BrainButtonStyle.BrainButtonStyle"),nullptr,LOAD_None,nullptr);
		const FButtonStyle* btnStyle = slateStyle->GetStyle<FButtonStyle>();
		FLinearColor color = FLinearColor(1,0.255,0,1);
		FSlateColor slateColor = FSlateColor(color);

		for (FString name : _saveFilesList)
		{
			UBrainLoadButtonWidget* btn = NewObject<UBrainLoadButtonWidget>(this);
			btn->WidgetStyle = *btnStyle;
			
			UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));
			text->ColorAndOpacity = slateColor;
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
