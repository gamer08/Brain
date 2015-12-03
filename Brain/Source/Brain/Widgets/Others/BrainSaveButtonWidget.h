// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainButtonWidget.h"
#include "BrainSaveButtonWidget.generated.h"

UCLASS()
class BRAIN_API UBrainSaveButtonWidget : public UBrainButtonWidget
{
	GENERATED_BODY()
	
public:
	UBrainSaveButtonWidget();
	
	UFUNCTION()
	void OnClick();
};