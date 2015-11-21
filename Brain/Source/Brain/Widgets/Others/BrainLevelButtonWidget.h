// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainButtonWidget.h"
#include "BrainLevelButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UBrainLevelButtonWidget : public UBrainButtonWidget
{
	GENERATED_BODY()
	
	public:
	UBrainLevelButtonWidget();
	
	UFUNCTION()
	void OnClick();
	
};
