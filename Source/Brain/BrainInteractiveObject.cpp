// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainInteractiveObject.h"
#include "BrainPlayerController.h"


// Sets default values
ABrainInteractiveObject::ABrainInteractiveObject()
{

	_mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	FName collisionProfileName(TEXT("Custom"));
	
	_mesh->BodyInstance.bSimulatePhysics = true;
	_mesh->bGenerateOverlapEvents = false;

	_mesh->SetCollisionProfileName(collisionProfileName);
	_mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	_mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	_mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	RootComponent = _mesh;

}

bool ABrainInteractiveObject::CanUseEnergy(float quantity)
{
	return ((ABrainPlayerController*)GetWorld()->GetFirstPlayerController())->GetEnergy() >= quantity;
}

void ABrainInteractiveObject::UseEnergy(float quantity)
{
	((ABrainPlayerController*)GetWorld()->GetFirstPlayerController())->SubEnergy(quantity);
}

