// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "MyObject.h"
#include "BrainGameMode.h"
#include "BrainGameInstance.h"

UMyObject::UMyObject()
{
	_number = 0.0f;
}

void UMyObject::Save(FBrainSaveData& saveData)
{
	FMyObjectSaveData dataToSave;
	dataToSave._loadFromfile = true;
	
	_number += 10.0f;

	dataToSave._number = _number;

	saveData.AddDataToSave(GetName(),dataToSave);
}

void UMyObject::Load()
{
	FMyObjectSaveData data;
	if (GetOuter())
	{
		if (UWorld* w = GetOuter()->GetWorld())
		{
			data = Cast<UBrainGameInstance>(w->GetGameInstance())->GetSaveManager()->GetDataFromSave<FMyObjectSaveData>("OBJ");
		}
	}
}

void UMyObject::LoadSavedData()
{
	Load();
}



