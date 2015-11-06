// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"
#include "Components/StaticMeshComponent.h"
#include "BrainGameInstance.h"
#include "Engine.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{
	_currentShearFirstAxis = _currentShearSecondAxis = 0.0f;
}

void ABrainNormalInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	int8 flags = (_canBeRotate ? EAction::ROTATE : 0)
		| (_canBeTranslate ? EAction::TRANSLATE : 0)
		| (_canBeScale ? EAction::SCALE : 0)
		| (_canBeShear ? EAction::SHEAR : 0);
	_actions = FObjectAction(flags);

	_cachedTransform = GetTransform();

	_shearMatrix = FMatrix(FVector(1, 0, 0),
								FVector(0, 1, 0), 
								FVector(0, 0, 1), 
								FVector(0, 0, 0));

	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
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

void ABrainNormalInteractiveObject::PerformAction7()
{
	if (_canBeShear)
		Shear(1);
}

void ABrainNormalInteractiveObject::PerformAction8()
{
	if (_canBeShear)
		Shear(-1);
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

void ABrainNormalInteractiveObject::Shear(int32 orientation)
{
	_currentShearFirstAxis += _firstAxisStep * orientation;
	_currentShearSecondAxis += _secondAxisStep * orientation;
	
	switch (_shearPlan)
	{
		case ShearPlan::XY:
			_shearMatrix = FMatrix(FVector(1, 0, _currentShearFirstAxis), 
									FVector(0, 1, _currentShearSecondAxis), 
									FVector(0, 0, 1), 
									FVector(0, 0, 0));
			break;

		case ShearPlan::XZ:
			_shearMatrix = FMatrix(FVector(1, _currentShearFirstAxis, 0), 
									FVector(0, 1, 0), 
									FVector(0, _currentShearSecondAxis, 1), 
									FVector(0, 0, 0));
			break;

		case ShearPlan::YZ:
			_shearMatrix = FMatrix(FVector(1, 0, 0),
									FVector(_currentShearFirstAxis, 1, 0),
									FVector(_currentShearSecondAxis, 0, 1), 
									FVector(0, 0, 0));
		break;

		default:
			break;
	}
	
	ApplyShear();
}

void ABrainNormalInteractiveObject::ApplyShear()
{
	FTransform sTrans = FTransform(_shearMatrix);	
	SetActorTransform(sTrans*_cachedTransform);
}

void ABrainNormalInteractiveObject::Save(FBrainSaveData& saveData)
{
	FBrainNIOSaveData dataToSave;

	dataToSave._loadFromfile = true;
	dataToSave._location = GetActorLocation();
	dataToSave._rotation = GetActorRotation();
	dataToSave._scale = GetActorScale();
	dataToSave._shearMatrix = _shearMatrix;

	saveData.AddDataToSave(GetName(),dataToSave);
}

void ABrainNormalInteractiveObject::Load()
{
	FString name = GetName();
	FBrainNIOSaveData savedData = Cast<UBrainGameInstance>(GetGameInstance())->GetSaveManager()->GetDataFromSave<FBrainNIOSaveData>(name);
	if (savedData._loadFromfile)
	{
		SetActorLocation(savedData._location);
		SetActorRotation(savedData._rotation);
		SetActorScale3D(savedData._scale);
			
		_shearMatrix = savedData._shearMatrix;
		_cachedTransform = GetTransform();
		ApplyShear();
	}
}
