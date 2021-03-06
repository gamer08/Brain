// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Brain.h"
#include "BrainCharacter.h"
#include "BrainPlayerController.h"
#include "BrainGameInstance.h"
#include "Engine.h"

// nouveau canal definis pour nos objets interactifs. Rajout� dans la configuration du projet. DefaultEngine.ini
#define INTERACTIVE_OBJECT ECC_GameTraceChannel2 

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ABrainCharacter::ABrainCharacter()
{
	//Empecher qu'Unreal cree des objets templates doublons pour les backup
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

		_minPitch = -89.0f;
		_maxPitch = 89.0f;
		_maxDistanceInteraction = 600.0f;

		PrimaryActorTick.bCanEverTick = true;

		USkeletalMeshComponent* mesh = GetMesh();
		mesh->bCastDynamicShadow = mesh->CastShadow = false;

		_selectedObject = nullptr;
	}
}

void ABrainCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitActionOnObjectDelegate();
	
	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
}

void ABrainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	ABrainInteractiveObject* selectedObj = CheckForInteractiveObjects();

	if (selectedObj != _selectedObject)
	{	
		if (selectedObj)
		{
			_selectedObject = selectedObj;
			Cast<ABrainPlayerController>(Controller)->SendSelectedObjectActionsToHUD(selectedObj->GetAvailableActions());
			_selectedObject->ApplySelectionColor();
		}
		else
		{
			Cast<ABrainPlayerController>(Controller)->SendSelectedObjectActionsToHUD(FObjectAction(-1));
			_selectedObject->ResetMaterialColor();
			_selectedObject = selectedObj;
		}

		_selectedAction = 0;
	}
}

void ABrainCharacter::InitActionOnObjectDelegate()
{
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction1);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction2);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction3);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction4);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction5);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction6);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction7);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction8);
}

void ABrainCharacter::MoveForward(float value)
{
	const FRotator Rotation = Cast<ABrainPlayerController>(Controller)->GetCameraRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void ABrainCharacter::MoveSide(float value)
{
	const FRotator Rotation = Cast<ABrainPlayerController>(Controller)->GetCameraRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void ABrainCharacter::Turn(float value)
{
	FRotator actorRotation = GetActorRotation();
	actorRotation.Yaw += value;
	SetActorRotation(actorRotation);
}

void ABrainCharacter::LookUp(float value)
{
	FRotator actorRotation = GetActorRotation();
	actorRotation.Pitch += value;
	LimitPitch(actorRotation, _minPitch, _maxPitch);
	SetActorRotation(actorRotation);
}

void ABrainCharacter::Jump()
{
	ACharacter::Jump();
}

void ABrainCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void ABrainCharacter::LimitPitch(FRotator& rotation, float minPitch, float maxPitch)
{
	rotation.Pitch = FMath::ClampAngle(rotation.Pitch, minPitch, maxPitch);
	rotation.Pitch = FRotator::ClampAxis(rotation.Pitch);
}

ABrainInteractiveObject* ABrainCharacter::CheckForInteractiveObjects()
{
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, this);
	
	traceParams.bTraceComplex = true;
	traceParams.bTraceAsyncScene = true;
	traceParams.bReturnPhysicalMaterial = true;
	
	FHitResult hit(ForceInit);

	UWorld* world = GetWorld();

	FVector startLocation = GetActorLocation() + FVector(0, 0, 64); // tweak pour prendre en compte la position de la camera.
	FVector endLocation = startLocation + (GetActorRotation().Vector() * _maxDistanceInteraction);

	world->SweepSingleByChannel(hit, startLocation, endLocation, FQuat::Identity, INTERACTIVE_OBJECT, FCollisionShape::MakeSphere(12.0f), traceParams);
	
	return Cast<ABrainInteractiveObject>(hit.GetActor());
}

void ABrainCharacter::PerformActionOnObject(int action)
{
	if (_selectedObject != nullptr)
		(_selectedObject->* (_actionObjects[action]))();
}

void ABrainCharacter::PerformSelectedAction(bool reversed)
{
	if (_selectedObject != nullptr)
	{
		_selectedObject->PerformActionNo(_selectedAction, reversed);
	}
}

void ABrainCharacter::Save(FBrainSaveData& saveData)
{
	FBrainCharacterSaveData dataToSave;

	dataToSave._loadFromfile = true;
	dataToSave._location = GetActorLocation();
	dataToSave._rotation = GetActorRotation();
	dataToSave._energy = _energy;
	
	saveData.AddDataToSave(dataToSave);
}

void ABrainCharacter::Load()
{
	if (!GetName().IsEmpty())
	{
		if (UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(GetGameInstance()))
		{
			if (UBrainSaveManager* saveManager = gameInstance->GetSaveManager())
			{
				FBrainCharacterSaveData savedData = saveManager->GetDataFromSave<FBrainCharacterSaveData>(GetName());

				if (savedData._loadFromfile)
				{
					SetActorLocation(savedData._location);
					SetActorRotation(savedData._rotation);
					_energy = savedData._energy;
				}
				else
				{
					SetActorRotation(FRotator(0));
					_energy = _maxEnergy;
				}
					
			}
		}
	}
}

void ABrainCharacter::AddEnergy(int32 energy)
{
	_energy += energy;
	if (_energy > _maxEnergy)
		_energy = _maxEnergy;
}

void ABrainCharacter::SubEnergy(int32 energy)
{
	_energy -= energy;
	if (_energy < 0)
		_energy = 0;
}

bool ABrainCharacter::HasEnergy()
{
	return _energy > 0;
}

int32 ABrainCharacter::GetEnergy()
{
	return _energy;
}

int32 ABrainCharacter::GetMaxEnergy()
{
	return _maxEnergy;
}

int32 ABrainCharacter::CountAvailableActions()
{
	if (_selectedObject != NULL)
		return _selectedObject->CountAvailableActions();
	else return 0;
}

void ABrainCharacter::SelectNextAction()
{
	_selectedAction++;
	int32 actionCount = CountAvailableActions();
	if (_selectedAction >= actionCount)
		_selectedAction -= actionCount;
	UE_LOG(LogTemp, Warning, TEXT("%d"), _selectedAction);
}

void ABrainCharacter::SelectLastAction()
{
	_selectedAction--;
	int32 actionCount = CountAvailableActions();
	if (_selectedAction < 0)
		_selectedAction += actionCount;
}

int32 ABrainCharacter::GetSelectedAction()
{
	return _selectedAction;
}