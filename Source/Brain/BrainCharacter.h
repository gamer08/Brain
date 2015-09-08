// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "BrainInteractiveObject.h"
#include "BrainCharacter.generated.h"

UCLASS(config=Game)
class ABrainCharacter : public ACharacter
{
	friend class ABrainPlayerController;
	GENERATED_BODY()

public:
	ABrainCharacter();

	// declaration du type de délégate. Un délégate = pointeur de fonction !
	typedef void(ABrainInteractiveObject::* ActionOnObjectFunction)(void);

protected:

	void MoveForward(float value);

	void MoveSide(float value);

	void Turn(float value);

	void LookUp(float value);

	void Jump();

	void StopJumping();

	void PerformActionOnObject(int action);

private:
	float _minPitch, _maxPitch;

	float _maxDistanceInteraction;

	// Array des délégates de type fonction de Interactive Object
	TArray<ActionOnObjectFunction> _actionObjects;

	UPROPERTY()
	ABrainInteractiveObject* _selectedObject;

	void Tick(float deltaTime) override;

	void BeginPlay() override;
	
	void InitActionOnObjectDelegate();

	void LimitPitch(FRotator& rotation, float minPitch, float maxPitch);
	
	ABrainInteractiveObject* CheckForInteractiveObjects();
};