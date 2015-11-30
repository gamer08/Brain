// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "GameplayObjects/BrainInteractiveObject.h"
#include "SaveSystem/BrainSaveInterface.h"
#include "BrainCharacter.generated.h"


UCLASS(config=Game)
class ABrainCharacter : public ACharacter, public IBrainSaveInterface
{
	friend class ABrainPlayerController;
	GENERATED_BODY()

public:
	ABrainCharacter();

	// declaration du type de délégate. Un délégate = pointeur de fonction !
	typedef void(ABrainInteractiveObject::* ActionOnObjectFunction)(void);

	void Save(FBrainSaveData& saveData);

	UFUNCTION(BlueprintCallable, Category = "Energy")
		void AddEnergy(int32 energy);

	UFUNCTION(BlueprintCallable, Category = "Energy")
		void SubEnergy(int32 energy);

	UFUNCTION(BlueprintCallable, Category = "Energy")
		bool HasEnergy();

	UFUNCTION(BlueprintCallable, Category = "Energy")
		int32 GetEnergy();

	UFUNCTION(BlueprintCallable, Category = "Energy")
		int32 GetMaxEnergy();

	void SelectNextAction();

	void SelectLastAction();

	UFUNCTION(BlueprintCallable, Category = "Energy")
		int32 GetSelectedAction();

	int32 CountAvailableActions();

protected:

	void MoveForward(float value);

	void MoveSide(float value);

	void Turn(float value);

	void LookUp(float value);

	void Jump();

	void StopJumping();

	void PerformActionOnObject(int action);

	void PerformSelectedAction(bool reversed);

private:

	// Array des délégates de type fonction de Interactive Object
	TArray<ActionOnObjectFunction> _actionObjects;

	float _minPitch, _maxPitch;

	float _maxDistanceInteraction;

	int32 _selectedAction;

	UPROPERTY()
	ABrainInteractiveObject* _selectedObject;

	void Tick(float deltaTime) override;

	void BeginPlay() override;
	
	void InitActionOnObjectDelegate();

	void LimitPitch(FRotator& rotation, float minPitch, float maxPitch);
	
	ABrainInteractiveObject* CheckForInteractiveObjects();

	void Load();

	UPROPERTY(EditAnywhere, Category = Energy, meta = (DisplayName = "Current Energy"))
		int32 _energy;

	UPROPERTY(EditAnywhere, Category = Energy, meta = (DisplayName = "Maximum Energy"))
		int32 _maxEnergy;

};
