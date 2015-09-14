// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{

}

void ABrainNormalInteractiveObject::PerformAction1()
{
	if (_canBeRotate)
		ChangeRotation(1);
}

void ABrainNormalInteractiveObject::PerformAction2()
{
	if (_canBeRotate)
		ChangeRotation(-1);
}

void ABrainNormalInteractiveObject::PerformAction3()
{
	if (_canBeTranslate)
		ChangePosition(1);
}

void ABrainNormalInteractiveObject::PerformAction4()
{
	if (_canBeTranslate)
		ChangePosition(-1);
}

void ABrainNormalInteractiveObject::PerformAction5()
{
	if (_canBeScale)
		ChangeScale(1);
}

void ABrainNormalInteractiveObject::PerformAction6()
{
	if (_canBeScale)
		ChangeScale(-1);
}

void ABrainNormalInteractiveObject::ChangeRotation(int32 orientation)
{
	FRotator rotation = GetActorRotation();
	SetActorRotation(rotation + (orientation * _rotationToApply));
}

void ABrainNormalInteractiveObject::ChangePosition(int32 orientation)
{
	FVector location = GetActorLocation();
	SetActorLocation(location + (orientation * _translationToApply));
}

void ABrainNormalInteractiveObject::ChangeScale(int32 orientation)
{
	FVector newScale = FVector(0);
	
	if (CanBeRescale(orientation, newScale))
		SetActorScale3D(newScale);
}

bool ABrainNormalInteractiveObject::CanBeRescale(int32 orientation, FVector& newScale)
{
	newScale = (GetActorScale3D() + (orientation * _scaleToApply));
	
	if ((newScale.Size() >= _minScale.Size()) && (newScale.Size() <= _maxScale.Size()))
		return true;
	else
		return false;

}