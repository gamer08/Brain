// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "BrainSaveSlotButtonWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class BRAIN_API UBrainSaveSlotButtonWidget : public UButton
{
	GENERATED_BODY()
	
public:
	UBrainSaveSlotButtonWidget();
	
	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	virtual void OnClick() PURE_VIRTUAL(UBrainSaveSlotButtonWidget::OnClick,);
	
};
