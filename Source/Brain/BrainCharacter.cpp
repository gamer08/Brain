// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Brain.h"
#include "BrainCharacter.h"
#include "BrainPlayerController.h"
#include "Engine.h"

// nouveau canal definis pour nos objets interactifs. Rajouté dans la configuration du projet. DefaultEngine.ini
#define INTERACTIVE_OBJECT ECC_GameTraceChannel2 

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

ABrainCharacter::ABrainCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	_minPitch = -89.0f;
	_maxPitch = 89.0f;
	_maxDistanceInteraction = 600.0f;

	//fait en sorte qu'un actor peut caller Tick();
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* mesh = GetMesh();
	mesh->bCastDynamicShadow = mesh->CastShadow = false;
}

void ABrainCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitActionOnObjectDelegate();
}

void ABrainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	ABrainInteractiveObject* selectedObj = CheckForInteractiveObjects();
	
	_selectedObject = selectedObj;
}

void ABrainCharacter::InitActionOnObjectDelegate()
{
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction1);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction2);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction3);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction4);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction5);
	_actionObjects.Add(&ABrainInteractiveObject::PerformAction6);

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
	
	//affiche le raycast à des fin de test
	DrawDebugLine(world, startLocation, endLocation, FColor::Green);
	
	return Cast<ABrainInteractiveObject>(hit.GetActor());
}

void ABrainCharacter::PerformActionOnObject(int action)
{
	if (_selectedObject != nullptr)
	{
		(_selectedObject->* (_actionObjects[action]))();
	}
}

