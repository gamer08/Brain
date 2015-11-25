// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BrainSaveMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UBrainSaveMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Save")
	void FillSavesList(UScrollBox* container);	

	void Save(FString name);	
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Save" )
	void CloseOnSaveSuccessfull();

private:

	UButton* CreateButton(const FButtonStyle* buttonStyle, FSlateColor textColor, FString text);

	UPROPERTY()
	TArray<FString> _saveFilesList;
};
