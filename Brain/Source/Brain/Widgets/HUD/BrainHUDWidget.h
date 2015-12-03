// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameplayObjects/BrainInteractiveObject.h"
#include "BrainHUDWidget.generated.h"

UCLASS()
class BRAIN_API UBrainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Name")
	FString _name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<bool> _availableActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<UTexture2D*> _actionTextures;

	UFUNCTION(BlueprintCallable, Category = "Action Bar")
	void SetAvailableAction(FObjectAction objectAction);
	
	//aucune implentation dans le code car c'est fait pour ce soit le blueprint qui fasse le travail. 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Action Bar" )
	void UpdateActionBar();

	UFUNCTION(BlueprintCallable, Category = "Action Bar")
	void LoadActionBarTextures();
};