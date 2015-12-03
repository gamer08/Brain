#pragma once

#include "FTransformation.generated.h"

UENUM(BlueprintType)
enum class TransformationType : uint8
{
	ROTATE UMETA(DisplayName = "Rotate"),
	TRANSLATE UMETA(DisplayName = "Translate"),
	SCALE UMETA(DisplayName = "Scale")
};

USTRUCT()
struct FTransformation
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Transformation type"))
		TransformationType _type;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (ClampMin = "0.1", Display = "Transformation speed"))
		float _speed;

	/*Rotation transformation Data*/
	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Rotation to Apply"))
		FRotator _rotation;

	/*Scale transformation data*/
	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Min Scale"))
		FVector _minScale;

	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Max Sclale"))
		FVector _maxScale;

	UPROPERTY()
		FVector _baseSclaleOverTimeValueInRAD;

	UPROPERTY()
		FVector _baseSclaleOverTimeStepInRAD;

	UPROPERTY()
		FVector _currentScaleInRAD;

	UPROPERTY()
		FVector _scaleRange;

	//Translation transformation Data
	UPROPERTY(EditAnywhere, Category = "Details", meta = (Display = "Translation to apply"))
		FVector _translation;

	FTransformation()
	{
		_translation = _minScale =
			_maxScale = _baseSclaleOverTimeValueInRAD = _baseSclaleOverTimeStepInRAD =
			_currentScaleInRAD = _scaleRange = FVector(0);
		_rotation = FRotator(0);
		_type = TransformationType::ROTATE;
		_speed = 1.0f;
	}
};