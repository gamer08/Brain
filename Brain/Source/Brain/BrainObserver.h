// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "GameplayObjects/BrainTimeInteractiveObject.h"
#include "BrainObserver.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAIN_API UBrainObserver : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBrainObserver();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// Write sthg in the console when notify is called by the observable
	virtual void Notify(bool state);
	
	UPROPERTY(EditAnywhere, Category = "Transformation", meta = (DisplayName = "Is Observer"))
		bool _isObserver;

	UPROPERTY(EditAnywhere, Category = "Transformation", meta = (DisplayName = "Transformation", EditCondition = "_isObserver"))
		FTransformation _transformation;


	

};
