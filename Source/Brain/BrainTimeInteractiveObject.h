// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "BrainTimeInteractiveObject.generated.h"

UENUM(BlueprintType)	
enum class TransformationType: uint8
{
    ROTATE UMETA(DisplayName ="Rotate"),
    TRANSLATE UMETA(DisplayName ="Translate"),
    SCALE UMETA(DisplayName ="Scale")
};

USTRUCT()
struct FTransformation
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Transformation"))
	FVector _transformation;
	
	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Transformation type"))
	TransformationType _type;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (ClampMin ="0.1", Display = "Transformation speed"))
	float _speed;

	FTransformation()
	{
		_transformation = FVector(0);
		_type = TransformationType::ROTATE;
		_speed = 1.0f;
	}
};

UCLASS()
class BRAIN_API ABrainTimeInteractiveObject : public ABrainInteractiveObject
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
	void ApplyTransformation(float deltaTime, const FTransformation& tranformation);

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
};


