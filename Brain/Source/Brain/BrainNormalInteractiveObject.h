// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "BrainSaveInterface.h"
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

	/*Rotation data*/
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Can be rotated"))
		bool _canBeRotate;

	UPROPERTY(EditAnywhere, Category = Animation, meta = (DisplayName = "Animation Duration"))
		float _animDuration;

	float _currentRotation;
	float _targetRotation;

	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation to Apply", EditCondition = "_canBeRotate"))
		FRotator _rotationToApply;

	/*Translation data*/
	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Can be moved"))
		bool _canBeTranslate;

	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Translation to apply", EditCondition = "_canBeTranslate"))
		FVector _translationToApply;

	float _currentTranslation;
	float _targetTranslation;

	/*Scale data*/
	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Can be Scaled"))
		bool _canBeScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Minimum scale", EditCondition = "_canBeScale"))
		int32 _minScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Maximum scale", EditCondition = "_canBeScale"))
		int32 _maxScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Scale Step", EditCondition = "_canBeScale"))
		int32 _scaleStep;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Init scale", EditCondition = "_canBeScale"))
		int32 _initScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Scale step to apply", ClampMin = "0.1", EditCondition = "_canBeScale"))
		FVector _scaleToApply;

	float _currentScale;
	float _targetScale;
	
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
