// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "BrainButtonWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class BRAIN_API UBrainButtonWidget : public UButton
{
	GENERATED_BODY()
	
public:
	UBrainButtonWidget();
	
	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	virtual void OnClick() PURE_VIRTUAL(UBrainButtonWidget::OnClick,);
	
};
