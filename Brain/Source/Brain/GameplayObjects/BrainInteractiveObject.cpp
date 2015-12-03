// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainInteractiveObject.h"
#include "Core/BrainPlayerController.h"

ABrainInteractiveObject::ABrainInteractiveObject()
{
	_mesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	FName collisionProfileName(TEXT("Custom"));
	
	_mesh->SetSimulatePhysics(true);

	_mesh->BodyInstance.bSimulatePhysics = true;
	_mesh->bGenerateOverlapEvents = false;

	_mesh->SetCollisionProfileName(collisionProfileName);
	_mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	_mesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);

	_mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	RootComponent = _mesh;
}

void ABrainInteractiveObject::BeginPlay()
{
	Super::BeginPlay();
	
	if (UMaterialInterface * mat = _mesh->GetMaterial(0))
	{
		_materialInstance = _mesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, mat);
		_materialInstance->GetVectorParameterValue(FName("color"), _defaultColor);
	}
}

bool ABrainInteractiveObject::CanUseEnergy(int32 quantity)
{
	return ((ABrainPlayerController*)GetWorld()->GetFirstPlayerController())->GetEnergy() >= quantity;
}

void ABrainInteractiveObject::UseEnergy(int32 quantity)
{
	((ABrainPlayerController*)GetWorld()->GetFirstPlayerController())->SubEnergy(quantity);
}

void ABrainInteractiveObject::PerformAction5()
{
}

void ABrainInteractiveObject::PerformAction6()
{
}

void ABrainInteractiveObject::PerformAction7()
{
}

void ABrainInteractiveObject::PerformAction8()
{	
}

void ABrainInteractiveObject::ApplySelectionColor()
{
	_materialInstance->SetVectorParameterValue(FName("color"), _selectionColor);
}

void ABrainInteractiveObject::ResetMaterialColor()
{
	_materialInstance->SetVectorParameterValue(FName("color"), _defaultColor);
}
