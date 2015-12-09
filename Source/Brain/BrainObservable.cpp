// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainObservable.h"

// Sets default values for this component's properties
UBrainObservable::UBrainObservable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UBrainObservable::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate Delegate, Delegate2;
	Delegate.BindUFunction(this, "OnActorCollisionBegin");
	Delegate2.BindUFunction(this, "OnActorCollisionEnd");

	GetOwner()->OnActorBeginOverlap.Add(Delegate);
	GetOwner()->OnActorEndOverlap.Add(Delegate2);
	
	for (int32 i = 0; i < _list.Num(); i++)
	{
		AActor* actor = _list[i];
		UBrainObserver* ub = actor->FindComponentByClass<UBrainObserver>();

		if (ub != nullptr)
			RegisterObserver(ub);
	}
}


// Called every frame
void UBrainObservable::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UBrainObservable::NotifyAll(bool state)
{
	for (int32 i=0; i < _list_observers.Num(); i++)
		_list_observers[i]->Notify(state);
}

void UBrainObservable::RegisterObserver(UBrainObserver* o)
{
	_list_observers.Add(o);
}

void UBrainObservable::UnregisterObserver(UBrainObserver* o)
{
	_list_observers.Remove(o);
}

void UBrainObservable::OnActorCollisionBegin(class AActor* OtherActor)
{
	if (_list_actors_overlap.Num() == 0)
	{
		NotifyAll(true);
		UE_LOG(LogTemp, Warning, TEXT("Begin !"));
	}

	_list_actors_overlap.Add(OtherActor);
}
void UBrainObservable::OnActorCollisionEnd(class AActor* OtherActor)
{
	_list_actors_overlap.Remove(OtherActor);
	if (_list_actors_overlap.Num() == 0)
	{
		NotifyAll(false);
		UE_LOG(LogTemp, Warning, TEXT("End !"));
	}
}