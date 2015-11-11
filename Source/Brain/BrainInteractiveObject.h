// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BrainEnums.h"
#include "BrainInteractiveObject.generated.h"


USTRUCT(BlueprintType)
struct FObjectAction
{
	GENERATED_USTRUCT_BODY();

	FObjectAction()
	{
	}

	FObjectAction(int32 flags)
	{
		_flags = flags;
	}

	UPROPERTY(BlueprintReadWrite)
	int32 _flags;

	bool GetValueForAction(EAction::Type action)
	{
		return (_flags &  action) != 0;
	}
};

UCLASS(Abstract)
class BRAIN_API ABrainInteractiveObject : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category=Interactive, meta = (DisplayName = "Name"))
	FName _name;

protected:
	
	UPROPERTY(Visibleanywhere, Category = Interactive, meta = (DisplayName = "Mesh"))
	UStaticMeshComponent* _mesh;
	
	UPROPERTY()
	FObjectAction _actions;

public:	
	ABrainInteractiveObject();

	const FObjectAction GetAvailableActions()
	{
		return _actions;
	}

	// declaration "virtuel pure" d'unreal

	UFUNCTION()
		virtual void PerformAction(int32 action) PURE_VIRTUAL(ABrainInteractiveObject::PerformAction, );
	UFUNCTION()
		virtual void CancelActions() PURE_VIRTUAL(ABrainInteractiveObject::CancelActions, );

	UFUNCTION()
		bool CanUseEnergy(float quantity);
	UFUNCTION()
		void UseEnergy(float quantity);
};
