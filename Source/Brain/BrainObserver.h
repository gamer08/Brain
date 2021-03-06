// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayObjects/FTransformation.h"
#include "SaveSystem/BrainSaveInterface.h"
#include "BrainEnums.h"
#include "BrainObserver.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAIN_API UBrainObserver : public UActorComponent, public IBrainSaveInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<FString, int8> _subjects;

	void Load();

public:		
	UPROPERTY(EditAnywhere, Category = "Transformation", meta = (DisplayName = "Is Observer"))
	bool _isObserver;	
	
	bool _state;

	UPROPERTY(EditAnywhere, Category = "Transformation", meta = (DisplayName = "Transformation", EditCondition = "_isObserver"))
	FTransformation _transformation;
	
	// Sets default values for this component's properties
	UBrainObserver();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Write sthg in the console when notify is called by the observable
	virtual void Notify(FString objectName, EObserverEvent::Type call);
	
	void UpdateState(FString objectName, int8 value);

	int8 CheckAllSwitches();

	void Save(FBrainSaveData& saveData);
};