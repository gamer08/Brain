// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainEndLevelTrigger.h"
#include "Core/BrainCharacter.h"
#include "BrainGameInstance.h"

ABrainEndLevelTrigger::ABrainEndLevelTrigger()
{
	_levelToLoad = FName();
}

void ABrainEndLevelTrigger::NotifyActorBeginOverlap(AActor* other)
{
	if (Cast<ABrainCharacter>(other))
	{
		if (UWorld* world = GetWorld())
		{
			if (UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(GetGameInstance()))
				gameInstance->GetSaveManager()->FlushCachedSaveData();
			
				UGameplayStatics::OpenLevel(world, _levelToLoad);
		}
	}
}