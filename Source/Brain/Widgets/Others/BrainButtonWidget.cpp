// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainButtonWidget.h"

UBrainButtonWidget::UBrainButtonWidget()
: Super()
{
	OnClicked.AddDynamic(this, &UBrainButtonWidget::OnClick);
}