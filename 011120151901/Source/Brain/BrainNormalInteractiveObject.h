// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BrainInteractiveObject.h"
#include "BrainNormalInteractiveObject.generated.h"


UCLASS()
class BRAIN_API ABrainNormalInteractiveObject : public ABrainInteractiveObject
{
	GENERATED_BODY()
	
private:

	/*Rotation data*/
	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Can be rotate"))
	bool _canBeRotate;

	UPROPERTY(EditAnywhere, Category = Rotation, meta = (DisplayName = "Rotation to Apply", EditCondition ="_canBeRotate"))
	FRotator _rotationToApply;

	/*Translation data*/
	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Can be move"))
	bool _canBeTranslate;

	UPROPERTY(EditAnywhere, Category = Translation, meta = (DisplayName = "Translation to apply", EditCondition ="_canBeTranslate"))
	FVector _translationToApply;
	
	/*Scale data*/
	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Can be Scale"))
	bool _canBeScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Minimum scale", ClampMin ="0.1", EditCondition ="_canBeScale"))
	FVector _minScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Maximum scale", ClampMin ="0.1", EditCondition ="_canBeScale"))
	FVector _maxScale;

	UPROPERTY(EditAnywhere, Category = Scale, meta = (DisplayName = "Scale step to apply", ClampMin = "0.1", EditCondition = "_canBeScale"))
	FVector _scaleToApply;

	
	/*Shear Data -- NE VA PAS ÊTRE UTILISABLE POUR L'INSTANT CAR BESOIN DE TEST ! - Fred*/
	UPROPERTY(/*EditAnywhere, Category = Shear, meta = (DisplayName = "Can be Shear")*/)
	bool _canBeShear;




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

	FVector MatrixMultiplication(FMatrix matrix, FVector vector);

public:

	ABrainNormalInteractiveObject();

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
};
