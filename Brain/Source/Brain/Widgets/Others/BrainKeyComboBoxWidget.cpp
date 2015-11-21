// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainKeyComboBoxWidget.h"
#include "ScaleBox.h"
#include "TextBlock.h"


UBrainKeyComboBoxWidget::UBrainKeyComboBoxWidget()
:Super()
{
	OnGenerateWidgetEvent.BindUFunction(this, "CreateComboBoxItem");
}

UWidget* UBrainKeyComboBoxWidget::CreateComboBoxItem(FString itemText)
{
	UScaleBox* scaleBox = NewObject<UScaleBox>(this, FName("scaleBox"));
	UTextBlock* text = NewObject<UTextBlock>(scaleBox, FName("text"));
	
	text->Justification = ETextJustify::Center;
	text->SetText(FText::FromString(itemText));
	FSlateColor color = text->ColorAndOpacity.UseForeground();
	text->SetColorAndOpacity(color);
	
	scaleBox->AddChild(text);

	return scaleBox;
}




