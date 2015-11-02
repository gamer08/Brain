// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainGameInstance.h"


UBrainGameInstance::UBrainGameInstance()
{
	if( !HasAnyFlags( RF_ClassDefaultObject | RF_ArchetypeObject ) )
	{
		_saveManager = NewObject<UBrainSaveManager>(this, FName("SaveManager"));
	}
	
}

void UBrainGameInstance::Init()
{
	Super::Init();
}

