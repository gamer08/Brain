// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainEndLevelTrigger.h"
#include "BrainCharacter.h"


ABrainEndLevelTrigger::ABrainEndLevelTrigger()
{

}

void ABrainEndLevelTrigger::NotifyActorBeginOverlap(AActor* other)
{
	if (Cast<ABrainCharacter>(other))
	{
		UWorld* world = GetWorld();
		if (world)
		{
			UGameplayStatics::OpenLevel(world, "test");
		}
	}
}

