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

	// Init Rotate
	_currentRotation = GetActorRotation();
	_targetRotation = GetActorRotation();
	_countRotation = 0;

	// Init Translate
	_currentTranslation = GetActorLocation();
	_targetTranslation = GetActorLocation();
	_countTranslation = 0;

	// Init Scale
	_targetScale = _initScale;
	_currentScale = _initScale;
	_countScale = 0;

	// Init Shear
	_countShear = 0;

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

void ABrainNormalInteractiveObject::CancelActions()
{
	//_targetRotation = FRotator(0, 0, 0);
	//_targetTranslation = _initScale;
	//_targetScale = _initScale;
}

void ABrainNormalInteractiveObject::ChangeRotation(int32 orientation)
{
	float energy = 0;
	if (_countRotation > 0)
		energy = orientation;
	else if (_countRotation < 0)
		energy = -orientation;
	else energy = 1;

	if (CanUseEnergy(energy))
	{
		_targetRotation = _currentRotation + (orientation * _rotationStep);
		_durationLeftRotation = 0;
		_countRotation += orientation;
		_deltaRotation = _targetRotation - _currentRotation;

		UseEnergy(energy);
	}
}

void ABrainNormalInteractiveObject::ChangePosition(int32 orientation)
{
	float energy = 0;
	if (_countTranslation > 0)
		energy = orientation;
	else if (_countTranslation < 0)
		energy = -orientation;
	else energy = 1;

	if (CanUseEnergy(energy))
	{
		_targetTranslation = _currentTranslation + (orientation * _translationStep);
		_durationLeftTranslation = 0;
		_countTranslation += orientation;
		_deltaTranslation = _targetTranslation - _currentTranslation;

		UseEnergy(energy);
	}
}

void ABrainNormalInteractiveObject::ChangeScale(int32 orientation)
{
	float energy = 0;

	if (_countScale > 0)
		energy = orientation;
	else if (_countScale < 0)
		energy = -orientation;
	else energy = 1;

	if (CanUseEnergy(energy))
	{
		_targetScale = _currentScale + (orientation * _scaleStep);
		_durationLeftScale = 0;
		_countScale += orientation;

		if (_targetScale.Size() < _minScale.Size())
			_targetScale = _minScale;
		else if (_targetScale.Size() > _maxScale.Size())
			_targetScale = _maxScale;
		else UseEnergy(energy);

		_deltaScale = _targetScale - _currentScale;
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
	//UE_LOG(LogTemp, Warning, TEXT("TEST %f"), _currentTranslation);

	if (_canBeRotate)
	{
		_currentRotation += (_deltaRotation * (deltaTime / _animDuration));
		_durationLeftRotation += deltaTime;
		if (_durationLeftRotation > _animDuration){
			_currentRotation = _targetRotation;
			_deltaRotation = FRotator(0, 0, 0); // Annulation du deltaRotation
		}

		SetActorRotation(_currentRotation);
	}

	if (_canBeTranslate)
	{
		_currentTranslation += (_deltaTranslation * deltaTime / _animDuration);
		_durationLeftTranslation += deltaTime;
		if (_durationLeftTranslation > _animDuration){
			_currentTranslation = _targetTranslation;
			_deltaTranslation = FVector(0, 0, 0); // Annulation du deltaSize
		}

		SetActorLocation(_currentTranslation);
	}


	if (_canBeScale)
	{

		_currentScale += (_deltaScale * deltaTime / _animDuration);
		_durationLeftScale += deltaTime;
		if (_durationLeftScale > _animDuration){
			_currentScale = _targetScale;
			_deltaScale = FVector(0,0,0); // Annulation du deltaSize
		}

		SetActorScale3D(_currentScale);
	}
}
