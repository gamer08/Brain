// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"
#include "Components/StaticMeshComponent.h"
#include "BrainGameInstance.h"
#include "Engine.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{
	_currentShearFirstAxis = _currentShearSecondAxis = 0.0f;

	PrimaryActorTick.bCanEverTick = true;
}

void ABrainNormalInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	int8 flags = (_canBeRotate ? EAction::ROTATE : 0)
		| (_canBeTranslate ? EAction::TRANSLATE : 0)
		| (_canBeScale ? EAction::SCALE : 0)
		| (_canBeShear ? EAction::SHEAR : 0);
	_actions = FObjectAction(flags);

	_targetScale = _initScale;
	_currentScale = _initScale;

	_cachedTransform = GetTransform();

	_shearMatrix = FMatrix(FVector(1, 0, 0),
								FVector(0, 1, 0), 
								FVector(0, 0, 1), 
								FVector(0, 0, 0));

	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
}

//void ABrainNormalInteractiveObject::PerformAction(int32 action)
//{
//	switch (action)
//	{
//	case 0:
//		if (_canBeRotate)
//			ChangeRotation(1);
//		break;
//	case 2:
//		if (_canBeTranslate)
//			ChangePosition(1);
//		break;
//	case 4:
//		if (_canBeScale)
//			ChangeScale(1);
//		break;
//	case 6:
//		if (_canBeShear)
//			Shear(1);
//		break;
//	case 1:
//		if (_canBeRotate)
//			ChangeRotation(-1);
//		break;
//	case 3:
//		if (_canBeTranslate)
//			ChangePosition(-1);
//		break;
//	case 5:
//		if (_canBeScale)
//			ChangeScale(-1);
//		break;
//	case 7:
//		if (_canBeShear)
//			Shear(-1);
//		break;
//	}
//}

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

void ABrainNormalInteractiveObject::CancelActions()
{
	_targetRotation = 0;
	_targetTranslation = 0;
	_targetScale = _initScale;
}

void ABrainNormalInteractiveObject::ChangeRotation(int32 orientation)
{
	float energy = 0;
	if (_targetRotation > 0)
		energy = orientation;
	else if (_targetRotation < 0)
		energy = -orientation;
	else energy = 1;
	if (CanUseEnergy(energy))
	{
		_targetRotation += orientation;
		UseEnergy(energy);
	}
}

void ABrainNormalInteractiveObject::ChangePosition(int32 orientation)
{
	float energy = 0;
	if (_targetTranslation > 0)
		energy = orientation;
	else if (_targetTranslation < 0)
		energy = -orientation;
	else energy = 1;
	if (CanUseEnergy(energy))
	{
		_targetTranslation += orientation;
		UseEnergy(energy);
	}
}

void ABrainNormalInteractiveObject::ChangeScale(int32 orientation)
{
	float energy = 0;
	if (_targetScale > 0)
		energy = orientation;
	else if (_targetScale < 0)
		energy = -orientation;
	else energy = 1;
	if (CanUseEnergy(energy))
	{
		_targetScale += orientation*_scaleStep;
		if (_targetScale < _minScale)
			_targetScale = _minScale;
		else if (_targetScale > _maxScale)
			_targetScale = _maxScale;
		else UseEnergy(energy);
	}

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

void ABrainNormalInteractiveObject::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	UE_LOG(LogTemp, Warning, TEXT("TEST %f"), _currentTranslation);

	if (_canBeRotate)
	{
		if (_currentRotation < _targetRotation)
		{
			_currentRotation += deltaTime / _animDuration;
			if (_currentRotation > _targetRotation)
				_currentRotation = _targetRotation;
		}
		else if (_currentRotation > _targetRotation)
		{
			_currentRotation -= deltaTime / _animDuration;
			if (_currentRotation < _targetRotation)
				_currentRotation = _targetRotation;
		}
		FRotator rotation = GetActorRotation();
		SetActorRotation(_rotationToApply*(_currentRotation * 1));
	}
	if (_canBeTranslate)
	{
		FVector initPos = GetActorLocation() - _currentTranslation*_translationToApply;
		if (_currentTranslation < _targetTranslation)
		{
			_currentTranslation += deltaTime / _animDuration;
			if (_currentTranslation > _targetTranslation)
				_currentTranslation = _targetTranslation;
		}
		else if (_currentTranslation > _targetTranslation)
		{
			_currentTranslation -= deltaTime / _animDuration;
			if (_currentTranslation < _targetTranslation)
				_currentTranslation = _targetTranslation;
		}
		SetActorLocation(initPos + _currentTranslation*_translationToApply);
	}
	if (_canBeScale)
	{
		if (_currentScale < _targetScale)
		{
			_currentScale += deltaTime / _animDuration;
			if (_currentScale > _targetScale)
				_currentScale = _targetScale;
		}
		else if (_currentScale > _targetScale)
		{
			_currentScale -= deltaTime / _animDuration;
			if (_currentScale < _targetScale)
				_currentScale = _targetScale;
		}
		SetActorScale3D(_currentScale*_scaleToApply);
	}
}
