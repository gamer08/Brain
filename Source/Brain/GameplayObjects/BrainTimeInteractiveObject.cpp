// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include <cmath>
#include "BrainGameInstance.h"
#include "BrainTimeInteractiveObject.h"

ABrainTimeInteractiveObject::ABrainTimeInteractiveObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABrainTimeInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	_globalTransformationSpeed = _defaultTransformationSpeed;

	int8 flags = (_canBeFastForward ? EAction::FASTFWRD : 0)
		| (_canBeSlowed ? EAction::SLOW : 0)
		| (_canBeStop ? EAction::STOP : 0)
		| (_canBeReversed ? EAction::REVERSE : 0);
	_actions = FObjectAction(flags);

	for (FTransformation& trans : _transformations)
		PreComputeTransformationData(trans);

	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
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

void ABrainTimeInteractiveObject::ApplyTransformation(float deltaTime, FTransformation& transformation)
{
	switch (transformation._type)
	{
		case TransformationType::ROTATE:
		{
			FRotator offset = (deltaTime * _globalTransformationSpeed  * transformation._speed) * transformation._rotation;
			SetActorRotation(GetActorRotation() + offset);
			break;
		}
			
		case TransformationType::SCALE:
		{
			FVector newScale;
			FVector scaleStep = FVector(transformation._baseSclaleOverTimeStepInRAD.X, 
				                        transformation._baseSclaleOverTimeStepInRAD.Y, 
										transformation._baseSclaleOverTimeStepInRAD.Z);

			scaleStep *= deltaTime * _globalTransformationSpeed  * transformation._speed;

			//Calculate new scale
			newScale.X = FMath::Sin(transformation._currentScaleInRAD.X + transformation._baseSclaleOverTimeValueInRAD.X + scaleStep.X);
			newScale.Y = FMath::Sin(transformation._currentScaleInRAD.Y + transformation._baseSclaleOverTimeValueInRAD.Y + scaleStep.Y);
			newScale.Z = FMath::Sin(transformation._currentScaleInRAD.Z + transformation._baseSclaleOverTimeValueInRAD.Z + scaleStep.Z);

			transformation._currentScaleInRAD += scaleStep;

			///Convert back to our scale range
			newScale.X = transformation._minScale.X + ((1.0f - ((1.0f - newScale.X) / 2.0f)) * transformation._scaleRange.X);
			newScale.Y = transformation._minScale.Y + ((1.0f - ((1.0f - newScale.Y) / 2.0f)) * transformation._scaleRange.Y);
			newScale.Z = transformation._minScale.Z + ((1.0f - ((1.0f - newScale.Z) / 2.0f)) * transformation._scaleRange.Z);
			
			SetActorScale3D(newScale);
			break;
		}

		case TransformationType::TRANSLATE:
		{
			FVector offset = (deltaTime * _globalTransformationSpeed  * transformation._speed) * transformation._translation;
			SetActorLocation(GetActorLocation() + offset,true);
			break;
		}
			
	default:
		break;

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

void ABrainTimeInteractiveObject::PreComputeTransformationData(FTransformation& transformation)
{
	switch (transformation._type)
	{

	case TransformationType::SCALE:

		FVector actorScale = GetActorScale();

		transformation._scaleRange = FVector(transformation._maxScale.X - transformation._minScale.X, 
			                                 transformation._maxScale.Y - transformation._minScale.Y, 
											 transformation._maxScale.Z - transformation._minScale.Z);
		
		// Manage division by 0
		float positionInBaseIntervalX, positionInBaseIntervalY, positionInBaseIntervalZ;
		positionInBaseIntervalX = positionInBaseIntervalY = positionInBaseIntervalZ = 1.0f;

		float x = ((transformation._maxScale.X - actorScale.X) / transformation._scaleRange.X);
		float y = ((transformation._maxScale.Y - actorScale.Y) / transformation._scaleRange.Y);
		float z = ((transformation._maxScale.Z - actorScale.Z) / transformation._scaleRange.Z);

		if (!std::isinf(x) && !std::isnan(x))
			positionInBaseIntervalX -= x;

		if (!std::isinf(y) && !std::isnan(y))
			positionInBaseIntervalY -= y;

		if (!std::isinf(z) && !std::isnan(z))
			positionInBaseIntervalZ -= z;

		//Take the value to -1 to 1 interval
		float positionInMinus1To1IntervalX = -1 + (positionInBaseIntervalX * 2);
		float positionInMinus1To1IntervalY = -1 + (positionInBaseIntervalY * 2);
		float positionInMinus1To1IntervalZ = -1 + (positionInBaseIntervalZ * 2);

		//Convert to RAD
		transformation._baseSclaleOverTimeValueInRAD.X = (FMath::Asin(positionInMinus1To1IntervalX));
		transformation._baseSclaleOverTimeValueInRAD.Y = (FMath::Asin(positionInMinus1To1IntervalY));
		transformation._baseSclaleOverTimeValueInRAD.Z = (FMath::Asin(positionInMinus1To1IntervalZ));

		//Calculate base step in RAD
		transformation._baseSclaleOverTimeStepInRAD.X = FMath::DegreesToRadians(transformation._scaleRange.X / 360.0f);
		transformation._baseSclaleOverTimeStepInRAD.Y = FMath::DegreesToRadians(transformation._scaleRange.Y / 360.0f);
		transformation._baseSclaleOverTimeStepInRAD.Z = FMath::DegreesToRadians(transformation._scaleRange.Z / 360.0f);

		break;

	}
}

void ABrainTimeInteractiveObject::Save(FBrainSaveData& saveData)
{
	FBrainTIOSaveData dataToSave;

	dataToSave._loadFromfile = true;
	dataToSave._location = GetActorLocation();
	dataToSave._rotation = GetActorRotation();
	dataToSave._scale = GetActorScale();
	dataToSave._globalTransformationSpeed = _globalTransformationSpeed;

	for (FTransformation& trans : _transformations)
	{
		FBrainTransformSaveData transformSaveData = FBrainTransformSaveData();
		transformSaveData._currentScaleInRAD = trans._currentScaleInRAD;

		dataToSave._transformsData.Add(transformSaveData);
	}

	saveData.AddDataToSave(GetName(),dataToSave);
}

void ABrainTimeInteractiveObject::Load()
{
	FString name = GetName();
	FBrainTIOSaveData savedData = Cast<UBrainGameInstance>(GetGameInstance())->GetSaveManager()->GetDataFromSave<FBrainTIOSaveData>(name);
	if (savedData._loadFromfile)
	{
		_globalTransformationSpeed = savedData._globalTransformationSpeed;
			
		int32 nbTransformations = _transformations.Num();

		SetActorLocation(savedData._location);
		SetActorRotation(savedData._rotation);
		SetActorScale3D(savedData._scale);
			
		for (int32 i = 0; i < nbTransformations; i++)
			_transformations[i]._currentScaleInRAD = savedData._transformsData[i]._currentScaleInRAD;
	}
}