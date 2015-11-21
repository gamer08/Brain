// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BrainLoadMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UBrainLoadMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Save")
	void FillSavesList(UScrollBox* container);	

	void LoadSave(FString name);

private:

	UPROPERTY()
	TArray<FString> _saveFilesList;

	
};
