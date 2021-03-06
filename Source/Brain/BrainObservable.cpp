// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainObservable.h"
#include "BrainGameInstance.h"

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

	if (UWorld* world = GetWorld())
	{
		if (UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance()))
		{
			if (UBrainSaveManager* saveManager = gameInstance->GetSaveManager())
			{
				//si on ne charge pas une sauvegarde le sujet s'identifie � ces observeurs.
				if (!saveManager->IsASaveLoaded())
					NotifyAll(GetOwner()->GetName(), EObserverEvent::HELLO);
			}
		}
	}
}


// Called every frame
void UBrainObservable::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UBrainObservable::NotifyAll(FString name, EObserverEvent::Type call)
{
	for (int32 i=0; i < _list_observers.Num(); i++)
		_list_observers[i]->Notify(name, call);
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
		NotifyAll(GetOwner()->GetName(), EObserverEvent::EVENTON);
		UE_LOG(LogTemp, Warning, TEXT("Begin !"));
	}

	_list_actors_overlap.Add(OtherActor);
}
void UBrainObservable::OnActorCollisionEnd(class AActor* OtherActor)
{
	_list_actors_overlap.Remove(OtherActor);
	if (_list_actors_overlap.Num() == 0)
	{
		NotifyAll(GetOwner()->GetName(), EObserverEvent::EVENTOFF);
		UE_LOG(LogTemp, Warning, TEXT("End !"));
	}
}