// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainObserver.h"
#include "BrainGameInstance.h"

// Sets default values for this component's properties
UBrainObserver::UBrainObserver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBrainObserver::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UBrainObserver::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UBrainObserver::UpdateState(FString objectName, bool value)
{
	_subjects[objectName] = value;

	bool canOpen = CheckAllSwitches();

	if (canOpen && !_state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation + _transformation._rotation);
		_state = true;
	}
	else if (!canOpen && _state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation - _transformation._rotation);
		_state = false;
	}
}

bool UBrainObserver::CheckAllSwitches()
{
	for (auto& Elem : _subjects)
	{
		if (Elem.Value == false)
			return false;	
	}
	return true;
}

void UBrainObserver::Notify(FString objectName, EObserverEvent::Type call)
{
	FRotator rotation = GetOwner()->GetActorRotation();
	FVector location = GetOwner()->GetActorLocation();
	
	switch (call)
	{
		case EObserverEvent::HELLO:
			_subjects.Emplace(objectName, false);
			break;

		case EObserverEvent::EVENTON:
			UpdateState(objectName, true);
			break;

		case EObserverEvent::EVENTOFF:
			UpdateState(objectName, false);
			break;

		default:
			break;
	}
}