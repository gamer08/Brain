// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainObserver.h"
#include "BrainGameInstance.h"

UBrainObserver::UBrainObserver()
{
	//Empecher qu'Unreal cree des objets templates doublons pour les backup
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
		// off to improve performance if you don't need them.
		bWantsBeginPlay = true;
		PrimaryComponentTick.bCanEverTick = true;
	}
}

// Called when the game starts
void UBrainObserver::BeginPlay()
{
	Super::BeginPlay();

	if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();
}

void UBrainObserver::Load()
{
	if (UWorld* world = GetWorld())
	{
		if (AActor* owner = GetOwner())
		{
			if (!owner->GetName().IsEmpty())
			{
				if (UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance()))
				{
					if (UBrainSaveManager* saveManager = gameInstance->GetSaveManager())
					{
						FBrainObserverSaveData savedData = saveManager->GetDataFromSave<FBrainObserverSaveData>(owner->GetName());
						if (savedData._loadFromfile)
						{
							_state = savedData._state;
							_subjects = savedData._subjects;

							if (_state)
							{
								FRotator rotation = GetOwner()->GetActorRotation();
								GetOwner()->SetActorRotation(rotation + _transformation._rotation);
							}
						}
					}
				}
			}
		}
	}
}

void UBrainObserver::Save(FBrainSaveData& saveData)
{
	FBrainObserverSaveData dataToSave;

	dataToSave._loadFromfile = true;
	dataToSave._state = _state;
	dataToSave._subjects = _subjects;

	saveData.AddDataToSave(GetOwner()->GetName(),dataToSave);
}

// Called every frame
void UBrainObserver::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UBrainObserver::UpdateState(FString objectName, int8 value)
{
	if (_subjects.Contains(objectName))
	_subjects[objectName] = value;

	int8 canOpen = CheckAllSwitches();

	if (canOpen == 1 && !_state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation + _transformation._rotation);
		_state = true;
	}
	else if (canOpen == 0 && _state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation - _transformation._rotation);
		_state = false;
	}
}

int8 UBrainObserver::CheckAllSwitches()
{
	for (auto& Elem : _subjects)
	{
		if (Elem.Value == 0)
			return 0;	
	}
	return 1;
}

void UBrainObserver::Notify(FString objectName, EObserverEvent::Type call)
{
	FRotator rotation = GetOwner()->GetActorRotation();
	FVector location = GetOwner()->GetActorLocation();
	
	switch (call)
	{
		case EObserverEvent::HELLO:
			_subjects.Emplace(objectName, 0);
			break;

		case EObserverEvent::EVENTON:
			UpdateState(objectName, 1);
			break;

		case EObserverEvent::EVENTOFF:
			UpdateState(objectName, 0);
			break;

		default:
			break;
	}
}