// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Volume.h"
#include "BrainEndLevelTrigger.generated.h"

UCLASS()
class BRAIN_API ABrainEndLevelTrigger : public AVolume
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = Level, meta = (DisplayName = "Level to load"))
	FName _levelToLoad;

public:
	ABrainEndLevelTrigger();

	void NotifyActorBeginOverlap(AActor* otherActor) override;
};