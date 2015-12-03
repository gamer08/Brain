// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainButtonWidget.h"
#include "BrainLoadButtonWidget.generated.h"

UCLASS()
class BRAIN_API UBrainLoadButtonWidget : public UBrainButtonWidget
{
	GENERATED_BODY()
	
public:
	UBrainLoadButtonWidget();
	
	UFUNCTION()
	void OnClick();	
};