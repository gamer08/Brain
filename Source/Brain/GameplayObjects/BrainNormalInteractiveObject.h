// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "SaveSystem/BrainSaveInterface.h"
#include "BrainNormalInteractiveObject.generated.h"


UENUM(BlueprintType)
enum class ShearPlan : uint8
{
	XY,
	XZ,
	YZ
};



UCLASS()
class BRAIN_API ABrainNormalInteractiveObject : public ABrainInteractiveObject, public IBrainSaveInterface
{
	GENERATED_BODY()
	
private:

	/* Animation Property */
	UPROPERTY(EditAnywhere, Category = Animation, meta = (DisplayName = "Animation Duration"))
		float _animDuration;

	/*Rotation data*/
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Can be rotated"))
		bool _canBeRotate;

	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation to Apply", EditCondition = "_canBeRotate"))
		FRotator _rotationStep;

	FRotator _currentRotation;
	FRotator _targetRotation;
	FRotator _deltaRotation;
	int _countRotation;
	float _durationLeftRotation;

	/*Translation data*/
	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Can be moved"))
		bool _canBeTranslate;

	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Translation to apply", EditCondition = "_canBeTranslate"))
		FVector _translationStep;

	FVector _currentTranslation;
	FVector _targetTranslation;
	FVector _deltaTranslation;
	int32 _countTranslation;
	float _durationLeftTranslation;


	/*Scale data*/
	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Can be Scaled"))
		bool _canBeScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Minimum scale", EditCondition = "_canBeScale"))
		FVector _minScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Maximum scale", EditCondition = "_canBeScale"))
		FVector _maxScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Scale Step", EditCondition = "_canBeScale"))
		FVector _scaleStep;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Init scale", EditCondition = "_canBeScale"))
		FVector _initScale;

	FVector _currentScale;
	FVector _targetScale;
	FVector _deltaScale; // For animation.
	int32 _countScale;
	float _durationLeftScale;
	
	/*Shear Data*/
	UPROPERTY(EditAnywhere, Category = Shear, meta = (DisplayName = "Can be Shear"))
		bool _canBeShear;

	UPROPERTY(EditAnywhere, Category = Shear, meta = (DisplayName = "Shear plan", EditCondition = "_canBeShear"))
		ShearPlan _shearPlan;

	UPROPERTY(EditAnywhere, Category = Shear, meta = (DisplayName = "First axis step", ClampMin = "0.0", EditCondition = "_canBeShear"))
		float _firstAxisStep;

	UPROPERTY(EditAnywhere, Category = Shear, meta = (DisplayName = "Second axis step", ClampMin = "0.0", EditCondition = "_canBeShear"))
		float _secondAxisStep;

	UPROPERTY()
		float _currentShearFirstAxis;

	UPROPERTY()
		float _currentShearSecondAxis;

	UPROPERTY()
		FMatrix _shearMatrix;

	UPROPERTY()
		FTransform _cachedTransform;

	int32 _countShear;


	void BeginPlay() override;

	UFUNCTION()
	void ChangeRotation(int32 orientation);

	UFUNCTION()
	void ChangePosition(int32 orientation);

	UFUNCTION()
	void ChangeScale(int32 orientation);
	
	bool CanBeRescale(int32 orientation, FVector& newScale);

	UFUNCTION()
	void Shear(int32 orientation);

	void ApplyShear();

	void Load();

public:

	ABrainNormalInteractiveObject();

	void Save(FBrainSaveData& saveData);

	//UFUNCTION()
	//	void PerformAction(int32 action) override;

	UFUNCTION()
	void PerformAction1();
	
	UFUNCTION()
	void PerformAction2();

	UFUNCTION()
	void PerformAction3();
	
	UFUNCTION()
	void PerformAction4();

	UFUNCTION()
	void PerformAction5() override;

	UFUNCTION()
	void PerformAction6() override;

	UFUNCTION()
	void PerformAction7() override;

	UFUNCTION()
	void PerformAction8() override;

	UFUNCTION()
		void CancelActions() override;

	void Tick(float deltaTime) override;
};
