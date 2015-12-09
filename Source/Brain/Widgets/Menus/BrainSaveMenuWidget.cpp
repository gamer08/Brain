// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveMenuWidget.h"
#include "BrainGameInstance.h"
#include "Widgets/Others/BrainSaveButtonWidget.h"

void UBrainSaveMenuWidget::FillSavesList(UScrollBox* container)
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
		
		//rajout d'une sauvegarde vide 
		container->AddChild(CreateButton(btnStyle, slateColor, FString("Nouvelle sauvegarde")));
		
		for (FString name : _saveFilesList)
			container->AddChild(CreateButton(btnStyle, slateColor, name));

		TArray<UPanelSlot*> slots = container->GetSlots();
		for (UPanelSlot* slot : slots)
		{
			if (UScrollBoxSlot* sSlot = Cast<UScrollBoxSlot>(slot))
				sSlot->SetPadding(FMargin(0, 0, 0, 5.0f));
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

UButton* UBrainSaveMenuWidget::CreateButton(const FButtonStyle* buttonStyle, FSlateColor textColor, FString textToDisplay)
{
	UBrainSaveButtonWidget* btn = NewObject<UBrainSaveButtonWidget>(this);
	btn->WidgetStyle = *buttonStyle;
		
	UTextBlock* text = NewObject<UTextBlock>(btn, FName("text"));
	text->ColorAndOpacity = textColor;
	text->SetText(FText::FromString(textToDisplay));

	btn->AddChild(text);

	return btn;
}