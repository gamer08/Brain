// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BrainObserver.h"
#include "BrainEnums.h"
#include "BrainObservable.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BRAIN_API UBrainObservable : public UActorComponent
{
	GENERATED_BODY()

private:
	TArray<UBrainObserver*> _list_observers;
	TArray<AActor*> _list_actors_overlap;

public:	
	// Sets default values for this component's properties
	UBrainObservable();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void NotifyAll(FString name, EObserverEvent::Type call);
	void RegisterObserver(UBrainObserver* o);
	void UnregisterObserver(UBrainObserver* o);


	UPROPERTY(EditAnywhere, Category = "Observer", meta = (DisplayName = "Can be Observed"))
	bool _bool;

	UPROPERTY(EditAnywhere, Category = "Observer", meta = (DisplayName = "My Observer", EditCondition = "_bool"))
	TArray<AActor*> _list;
	
	UFUNCTION()
	void OnActorCollisionBegin(class AActor* OtherActor);

	UFUNCTION()
	void OnActorCollisionEnd(class AActor* OtherActor);
};
