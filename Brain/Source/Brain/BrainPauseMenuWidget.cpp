// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainGameInstance.h"
#include "BrainPauseMenuWidget.h"


void UBrainPauseMenuWidget::RestartLevel()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UBrainGameInstance* gameInstance = Cast<UBrainGameInstance>(world->GetGameInstance());

		if (gameInstance)
		{
			gameInstance->GetSaveManager()->FlushCachedSaveData();
			UGameplayStatics::OpenLevel(world,FName(*world->GetName()));
		}
	}
}

