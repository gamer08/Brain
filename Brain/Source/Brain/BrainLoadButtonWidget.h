// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainSaveSlotButtonWidget.h"
#include "BrainLoadButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UBrainLoadButtonWidget : public UBrainSaveSlotButtonWidget
{
	GENERATED_BODY()
	
	public:
	UBrainLoadButtonWidget();
	
	UFUNCTION()
	void OnClick();
	
};
