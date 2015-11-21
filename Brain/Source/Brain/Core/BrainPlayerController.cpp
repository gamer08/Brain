// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainPlayerController.h"
#include "BrainCameraManager.h"
#include "BrainGameInstance.h"
#include "BrainHUD.h"
#include "BrainGameMode.h"

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

void ABrainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Pour être sur que le controller recoive les input apres un chargement de sauvegarde
	FInputModeGameOnly inputMode = FInputModeGameOnly();
	this->SetInputMode(inputMode);
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
	InputComponent->BindAction("PerformActionOnObject7", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<6>);
	InputComponent->BindAction("PerformActionOnObject8", IE_Pressed, this, &ABrainPlayerController::PerformActionOnObject<7>);
	InputComponent->BindAction("Pause", IE_Pressed, this, &ABrainPlayerController::ShowPauseMenu);

	InputComponent->BindAxis("MoveForward", this, &ABrainPlayerController::MoveForward);
	InputComponent->BindAxis("MoveBackward", this, &ABrainPlayerController::MoveForward);

	InputComponent->BindAxis("MoveLeft", this, &ABrainPlayerController::MoveSide);
	InputComponent->BindAxis("MoveRight", this, &ABrainPlayerController::MoveSide);

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
	// Le -1 en début de paramètres est à remplacer par une variable pour donner le choix au joueur plus tard dans les options.

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

void ABrainPlayerController::SendSelectedObjectActionsToHUD(FObjectAction actions)
{
	Cast<ABrainHUD>(MyHUD)->OnReceiveSelectedObjectActions(actions);
}

void ABrainPlayerController::GiveControlsToUI(bool value)
{
	this->bShowMouseCursor = value;
	this->bEnableClickEvents = value;
	this->bEnableMouseOverEvents = value;

	if (value)
	{
		FInputModeUIOnly inputMode = FInputModeUIOnly();
		this->SetInputMode(inputMode);
	}
	else
	{
		FInputModeGameOnly inputMode = FInputModeGameOnly();
		this->SetInputMode(inputMode);
	}
}

void ABrainPlayerController::ShowPauseMenu()
{
	UWorld* world = GetWorld();
	if (world)
	{
		ABrainGameMode* gameMode = Cast<ABrainGameMode>(world->GetAuthGameMode());
		if (gameMode)
		{
			UGameplayStatics::SetGamePaused(world,true);
			GiveControlsToUI(true);
			gameMode->CreatePauseMenu();
		}
	}
}

float ABrainPlayerController::GetEnergy()
{
	return _pawn->GetEnergy();
}

void ABrainPlayerController::SubEnergy(float quantity)
{
	_pawn->SubEnergy(quantity);
}