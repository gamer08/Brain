// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{

}

void ABrainNormalInteractiveObject::PerformAction1()
{
	if (_canBeRotate)
		IncreaseRotation();
}

void ABrainNormalInteractiveObject::PerformAction2()
{
	if (_canBeRotate)
		DecreaseRotation();
}

void ABrainNormalInteractiveObject::IncreaseRotation()
{
	FRotator rotation = GetActorRotation();
	SetActorRotation(rotation + _rotationToApply);
}

void ABrainNormalInteractiveObject::DecreaseRotation()
{
	FRotator rotation = GetActorRotation();
	SetActorRotation(rotation - _rotationToApply);
}