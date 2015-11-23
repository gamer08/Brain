// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainCameraManager.h"
#include "BrainGameInstance.h"

ABrainCameraManager::ABrainCameraManager()
{
	_minPitch = -89.0f;
	_maxPitch = 89.0f;
	_relativePosition = FVector(0.0f, 0.0f, 64.0f);
	_rotation = FRotator(0.0f);
}

void ABrainCameraManager::BeginPlay()
{
	Super::BeginPlay();

	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
}

void ABrainCameraManager::UpdateViewTarget(FTViewTarget& outVT, float deltaTime)
{
	//Construit une matice de rotation a partir de Yaw et Pitch pur calculer la nouvelle position relative 
	FRotationMatrix cameraRotation(FRotator(_rotation.Pitch, _rotation.Yaw, 0.0f));
	
	outVT.POV.Location = outVT.Target->GetActorLocation() + cameraRotation.TransformPosition(_relativePosition);
	outVT.POV.Rotation = _rotation;
}

void ABrainCameraManager::UpdateYaw(float value)
{
	_rotation.Yaw += value;
}

void ABrainCameraManager::UpdatePitch(float value)
{
	_rotation.Pitch += value;
	LimitPitch(_rotation, _minPitch, _maxPitch);
}

void ABrainCameraManager::LimitPitch(FRotator& rotation, float minPitch, float maxPitch)
{
	rotation.Pitch = FMath::ClampAngle(rotation.Pitch, minPitch, maxPitch);
	rotation.Pitch = FRotator::ClampAxis(rotation.Pitch);
}

void ABrainCameraManager::Save(FBrainSaveData& saveData)
{
	FBrainCameraSaveData dataToSave;

	dataToSave._loadFromfile = true;
	dataToSave._rotation = _rotation;

	saveData.AddDataToSave(dataToSave);
}

void ABrainCameraManager::Load()
{
	FString name = GetName();
	FBrainCameraSaveData savedData = Cast<UBrainGameInstance>(GetGameInstance())->GetSaveManager()->GetDataFromSave<FBrainCameraSaveData>(name);
	if (savedData._loadFromfile)
		_rotation = savedData._rotation;
}