// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BrainSaveInterface.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UMyObject : public UObject, public IBrainSaveInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	float _number;
	
public:
	UMyObject();

	void Save(FBrainSaveData& saveData);
	FMyObjectSaveData LoadSavedData();
	
};
