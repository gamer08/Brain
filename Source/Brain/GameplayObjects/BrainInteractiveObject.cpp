// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainInteractiveObject.h"
#include "Core/BrainPlayerController.h"


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

void ABrainInteractiveObject::PerformActionNo(int id, bool reverseAction)
{
	int32 actionId = _actions.GetActionNo(id);
	UE_LOG(LogTemp, Warning, TEXT("%d => %d"), id, actionId);

	switch (actionId)
	{
	case 0:
		reverseAction ? PerformAction2() : PerformAction1();
		break;
	case 1:
		reverseAction ? PerformAction4() : PerformAction3();
		break;
	case 2:
		reverseAction ? PerformAction6() : PerformAction5();
		break;
	case 3:
		reverseAction ? PerformAction8() : PerformAction7();
		break;
	case 4:
		reverseAction ? PerformAction2() : PerformAction1();
		break;
	case 5:
		reverseAction ? PerformAction4() : PerformAction3();
		break;
	case 6:
		reverseAction ? PerformAction6() : PerformAction5();
		break;
	case 7:
		reverseAction ? PerformAction8() : PerformAction7();
		break;
	}
}