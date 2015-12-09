// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BrainLevelSelectionMenuWidget.generated.h"

UCLASS()
class BRAIN_API UBrainLevelSelectionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FString> _levelList;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Brain")
	void FillLevelsList(UScrollBox* container);	

	void LoadLevel(FString name);
};
