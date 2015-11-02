// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/Button.h"
#include "BrainSaveSlotButtonWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadDelegate, FString, name);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class BRAIN_API UBrainSaveSlotButtonWidget : public UButton
{
	GENERATED_BODY()
	
public:
	UBrainSaveSlotButtonWidget();

	UPROPERTY()
	FLoadDelegate load;
	
	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void LoadGameFile(FString name);
	
};
