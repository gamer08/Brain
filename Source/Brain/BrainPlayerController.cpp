// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainPlayerController.h"
#include "BrainCameraManager.h"

ABrainPlayerController::ABrainPlayerController()
{
	PlayerCameraManagerClass = ABrainCameraManager::StaticClass();
	_cameraRotationSpeed = 100.0f;
}

void ABrainPlayerController::Possess(APawn* pawn)
{
	// cast plus rapide, mais lance une exception si null - dans le cas présent je suis toujours sur que pawn est un APawn donc ca va
	_pawn = CastChecked<ABrainCharacter>(pawn);

	Super::Possess(pawn);
}


void ABrainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Jump", IE_Pressed, this, &ABrainPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABrainPlayerController::StopJumping);

	InputComponent->BindAction("PerformActionOnObject1", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<0>);
	InputComponent->BindAction("PerformActionOnObject2", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<1>);
	InputComponent->BindAction("PerformActionOnObject3", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<2>);
	InputComponent->BindAction("PerformActionOnObject4", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<3>);
	InputComponent->BindAction("PerformActionOnObject5", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<4>);
	InputComponent->BindAction("PerformActionOnObject6", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<5>);

	
	InputComponent->BindAxis("MoveForward", this, &ABrainPlayerController::MoveForward);
	InputComponent->BindAxis("MoveSide", this, &ABrainPlayerController::MoveSide);

	InputComponent->BindAxis("Turn", this, &ABrainPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &ABrainPlayerController::LookUp);

}

void ABrainPlayerController::MoveForward(float value)
{
	if (value != 0.0)
		_pawn->MoveForward(value);
}

void ABrainPlayerController::MoveSide(float value)
{
	if (value != 0.0)
		_pawn->MoveSide(value);
}

void ABrainPlayerController::Turn(float value)
{
	Cast<ABrainCameraManager>(PlayerCameraManager)->UpdateYaw(value * GetWorld()->GetDeltaSeconds() * _cameraRotationSpeed);
	_pawn->Turn(value * GetWorld()->GetDeltaSeconds() * _cameraRotationSpeed);
}

void ABrainPlayerController::LookUp(float value)
{
	Cast<ABrainCameraManager>(PlayerCameraManager)->UpdatePitch(-1 * value * GetWorld()->GetDeltaSeconds() * _cameraRotationSpeed);
	_pawn->LookUp(-1 * value * GetWorld()->GetDeltaSeconds() * _cameraRotationSpeed);
}

void ABrainPlayerController::Jump()
{
	_pawn->Jump();
}

void ABrainPlayerController::StopJumping()
{
	_pawn->StopJumping();
}