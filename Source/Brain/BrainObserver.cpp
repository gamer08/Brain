// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainObserver.h"


// Sets default values for this component's properties
UBrainObserver::UBrainObserver()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBrainObserver::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBrainObserver::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UBrainObserver::Notify(bool state)
{
	
	FRotator rotation = GetOwner()->GetActorRotation();
	FVector location = GetOwner()->GetActorLocation();
	

	switch (_transformation._type)
	{
	case TransformationType::ROTATE:
	
		if (state)
			GetOwner()->SetActorRotation(rotation + _transformation._rotation);
		
		else
			GetOwner()->SetActorRotation(rotation - _transformation._rotation);
		break;

	case TransformationType::TRANSLATE:
		
		if (state)
			GetOwner()->SetActorLocation(location + _transformation._translation);
		
		else
			GetOwner()->SetActorLocation(location - _transformation._translation);

		break;
	default:
		break;
	}
	
}

