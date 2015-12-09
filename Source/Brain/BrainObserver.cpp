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
	/*if (this->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass()))
		Load();*/
}

// Called every frame
void UBrainObserver::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UBrainObserver::updateState(FString objectName, bool value)
{
	client[objectName] = value;

	bool canOpen = checkAllSwitches();

	if (canOpen && !state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation + _transformation._rotation);
		state = true;
	}
	else if (!canOpen && state)
	{
		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation - _transformation._rotation);
		state = false;
	}
}

bool UBrainObserver::checkAllSwitches()
{
	for (auto& Elem : client)
	{
		if (Elem.Value == false)
		{
			return false;
		}
			
	}
	return true;

	/*if (canOpen)
	{
		state = true;

		FRotator rotation = GetOwner()->GetActorRotation();
		GetOwner()->SetActorRotation(rotation + _transformation._rotation);
		return true;
	}*/
}

void UBrainObserver::Notify(FString objectName, EObserverEvent::Type call)
{
	FRotator rotation = GetOwner()->GetActorRotation();
	FVector location = GetOwner()->GetActorLocation();
	
	switch (call)
	{
	case EObserverEvent::HELLO:
		client.Emplace(objectName, false);
		break;

	case EObserverEvent::EVENTON:
		updateState(objectName, true);
		break;

	case EObserverEvent::EVENTOFF:
		updateState(objectName, false);

		break;
	}



	//switch (_transformation._type)
	//{
	//case TransformationType::ROTATE:
	//
	//	if (state)
	//		GetOwner()->SetActorRotation(rotation + _transformation._rotation);
	//	else
	//		GetOwner()->SetActorRotation(rotation - _transformation._rotation);
	//	
	//	break;

	//case TransformationType::TRANSLATE:
	//	
	//	if (state)
	//		GetOwner()->SetActorLocation(location + _transformation._translation);
	//	else
	//		GetOwner()->SetActorLocation(location - _transformation._translation);

	//	break;
	//
	//default:
	//	break;
	//}	
}

//void UBrainObserver::Save(FBrainSaveData& saveData)
//{
//	FBrainTIOSaveData dataToSave;
//
//	dataToSave._loadFromfile = true;
//	dataToSave._location = GetOwner()->GetActorLocation();
//	dataToSave._rotation = GetOwner()->GetActorRotation();
//	saveData.AddDataToSave(GetName(), dataToSave);
//}
//
//void UBrainObserver::Load()
//{
//	if (!GetName().IsEmpty())
//	{
//		if (UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(GetOwner()->GetGameInstance()))
//		{
//			if (UBrainSaveManager* saveManager = gameInstance->GetSaveManager())
//			{
//				FBrainTIOSaveData savedData = saveManager->GetDataFromSave<FBrainTIOSaveData>(GetName());
//				if (savedData._loadFromfile)
//				{
//					GetOwner()->SetActorLocation(savedData._location);
//					GetOwner()->SetActorRotation(savedData._rotation);
//				}
//			}
//		}
//	}
//}