// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainTimeInteractiveObject.h"

ABrainTimeInteractiveObject::ABrainTimeInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABrainTimeInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	_globalTransformationSpeed = _defaultTransformationSpeed;
}

void ABrainTimeInteractiveObject::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	ApplyTransformations(deltaTime);
}

void ABrainTimeInteractiveObject::ApplyTransformations(float deltaTime)
{
	for (FTransformation& trans : _transformations)
	{
		ApplyTransformation(deltaTime, trans);
	}
}

void ABrainTimeInteractiveObject::ApplyTransformation(float deltaTime, const FTransformation& transformation)
{
	switch (transformation._type)
	{
		case TransformationType::ROTATE:
		{
			FRotator rotationToApply = FRotator(transformation._transformation.Y, transformation._transformation.Z, transformation._transformation.X);
			FRotator offset = (deltaTime * _globalTransformationSpeed  * transformation._speed) * rotationToApply;
			SetActorRotation(GetActorRotation() + offset);
		}
	}
}


void ABrainTimeInteractiveObject::PerformAction1()
{
	if (_canBeFastForward)
		FastForward();
}

void ABrainTimeInteractiveObject::PerformAction2()
{
	if (_canBeSlowed)
		Slow();
}

void ABrainTimeInteractiveObject::PerformAction3()
{
	if (_canBeStop)
		Stop();
}

void ABrainTimeInteractiveObject::PerformAction4()
{
	if (_canBeReversed)
		Reverse();
}

void ABrainTimeInteractiveObject::FastForward()
{
	_globalTransformationSpeed = _globalTransformationSpeed == _fastForwardScale ? _defaultTransformationSpeed : _fastForwardScale;
}

void ABrainTimeInteractiveObject::Slow()
{
	_globalTransformationSpeed = _globalTransformationSpeed == _slowScale ? _defaultTransformationSpeed : _slowScale;
}

void ABrainTimeInteractiveObject::Stop()
{
	_globalTransformationSpeed = _globalTransformationSpeed == 0.0f ? _defaultTransformationSpeed : 0.0f;
}

void ABrainTimeInteractiveObject::Reverse()
{
	_globalTransformationSpeed = _globalTransformationSpeed == _reverseScale ? _defaultTransformationSpeed : _reverseScale;
}