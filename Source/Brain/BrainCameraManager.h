// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "BrainSaveInterface.h"
#include "BrainCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API ABrainCameraManager : public APlayerCameraManager,  public IBrainSaveInterface
{
	GENERATED_BODY()
	
private:
	float _minPitch, _maxPitch;
	FVector _relativePosition;
	FRotator _rotation;

	void BeginPlay() override;
	void LimitPitch(FRotator& rotation, float minPitch, float maxPitch);
	void UpdateViewTarget(FTViewTarget& outVT, float deltaTime) override; 
	
	void Load();

public:

	ABrainCameraManager();
	
	void UpdatePitch(float value);
	void UpdateYaw(float value);

	void Save(FBrainSaveData& saveData);
	
};