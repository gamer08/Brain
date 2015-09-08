// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "BrainNormalInteractiveObject.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API ABrainNormalInteractiveObject : public ABrainInteractiveObject
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = Rotation, meta = (Display = "Can be rotate"))
	bool _canBeRotate;

	UPROPERTY(EditAnywhere, Category = Rotation, meta = (Display = "Rotation to Apply", EditCondition ="_canBeRotate"))
	FRotator _rotationToApply;


	UFUNCTION()
	void IncreaseRotation();

	UFUNCTION()
	void DecreaseRotation();


public:

	ABrainNormalInteractiveObject();

	UFUNCTION()
	void PerformAction1();
	
	UFUNCTION()
	void PerformAction2();
};
