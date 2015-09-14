// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BrainCharacter.h"
#include "BrainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API ABrainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	ABrainCharacter* _pawn;

	float _cameraRotationSpeed;

	void MoveForward(float value);
	void MoveSide(float value);
	void Turn(float value);
	void LookUp(float value);
	void Jump();
	void StopJumping();

	template<int action>
	void PerformActionOnObject()
	{
		_pawn->PerformActionOnObject(action);
	}

	virtual void SetupInputComponent() override;
	virtual void Possess(APawn* aPawn) override;

public:
	ABrainPlayerController();

	FORCEINLINE FRotator GetCameraRotation() const
	{ 
		return PlayerCameraManager->GetCameraRotation(); 
	}
};