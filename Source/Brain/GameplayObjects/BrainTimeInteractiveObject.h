// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "SaveSystem/BrainSaveInterface.h"
#include "FTransformation.h"
#include "BrainTimeInteractiveObject.generated.h"

UCLASS()
class BRAIN_API ABrainTimeInteractiveObject : public ABrainInteractiveObject, public IBrainSaveInterface
{
	GENERATED_BODY()

private:

	float _globalTransformationSpeed;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (DisplayName = "Default Speed"))
	float _defaultTransformationSpeed;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (DisplayName = "Transformations"))
	TArray<FTransformation> _transformations;

	/*Fast Forward data*/
	UPROPERTY(EditAnywhere, Category = "Fast Forward", meta = (DisplayName = "Can be fast forward"))
	bool _canBeFastForward;

	UPROPERTY(EditAnywhere, Category = "Fast Forward", meta = (DisplayName = "Fast forward scale", ClampMin ="1.1", EditCondition ="_canBeFastForward"))
	float _fastForwardScale;

	/*Slow data*/
	UPROPERTY(EditAnywhere, Category = "Slow", meta = (DisplayName = "Can be slow down"))
	bool _canBeSlowed;

	UPROPERTY(EditAnywhere, Category = "Slow", meta = (DisplayName = "Slow scale", EditCondition ="_canBeSlowed"))
	float _slowScale;

	/*Stop data*/
	UPROPERTY(EditAnywhere, Category = "Stop", meta = (DisplayName = "Can be stop"))
	bool _canBeStop;

	/*Reverse data*/
	UPROPERTY(EditAnywhere, Category = "Reverse", meta = (DisplayName = "Can be Reverse"))
	bool _canBeReversed;

	UPROPERTY(EditAnywhere, Category = "Reverse", meta = (DisplayName = "Reverse scale", ClampMax ="-0.1", EditCondition ="_canBeReversed"))
	float _reverseScale;


	UFUNCTION()
	void FastForward();

	UFUNCTION()
	void Slow();

	UFUNCTION()
	void Stop();

	UFUNCTION()
	void Reverse();

	void ApplyTransformations(float deltaTime);
	void ApplyTransformation(float deltaTime, FTransformation& tranformation);
	void PreComputeTransformationData(FTransformation& transformation);

	void Load();

public:
	ABrainTimeInteractiveObject();

	void Tick(float deltaTime) override;
	void BeginPlay() override;
	
	UFUNCTION()
	void PerformAction1();
	
	UFUNCTION()
	void PerformAction2();

	UFUNCTION()
	void PerformAction3();
	
	UFUNCTION()
	void PerformAction4();	

	void Save(FBrainSaveData& saveData);
};