// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ComboBoxString.h"
#include "Widget.h"
#include "BrainKeyComboBoxWidget.generated.h"

UCLASS()
class BRAIN_API UBrainKeyComboBoxWidget : public UComboBoxString
{
	GENERATED_BODY()
	
public:
	UBrainKeyComboBoxWidget();

protected: 
	UFUNCTION()
	UWidget* CreateComboBoxItem(FString text);
};