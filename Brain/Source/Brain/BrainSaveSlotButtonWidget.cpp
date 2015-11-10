// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveSlotButtonWidget.h"

UBrainSaveSlotButtonWidget::UBrainSaveSlotButtonWidget()
: Super()
{
		OnClicked.AddDynamic(this, &UBrainSaveSlotButtonWidget::OnClick);
}

/*void UBrainSaveSlotButtonWidget::OnClick()
{
}*/

