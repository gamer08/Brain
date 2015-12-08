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

	int32 CountAvailableActions()
	{
		int32 count = 0;
		for (int32 i = 0; i < 8; i++)
		{
			if (((1 << i) & _flags) != 0)
				count++;
		}
		return count;
	}

	int32 GetActionNo(int32 id)
	{
		int32 count = id;
		for (int32 i = 0; i < 8; i++)
		{
			if (((1 << i) & _flags) != 0)
				count--;
			if (count < 0)
				return i;
			
		}
		return -1;
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

	int32 CountAvailableActions()
	{
		return _actions.CountAvailableActions();
	}

	// declaration "virtuel pure" d'unreal

//	UFUNCTION()
//		virtual void PerformAction(int32 action) PURE_VIRTUAL(ABrainInteractiveObject::PerformAction, );
	

	// declaration "virtuel pure" d'unreal
	UFUNCTION()
	virtual void PerformAction1() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction1,);
	
	UFUNCTION()
	virtual void PerformAction2() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction2,);

	UFUNCTION()
	virtual void PerformAction3() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction3,);

	UFUNCTION()
	virtual void PerformAction4() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction4,);

	/*Plus a venir....*/

	UFUNCTION()
	virtual void PerformAction5();

	UFUNCTION()
	virtual void PerformAction6();

	UFUNCTION()
	virtual void PerformAction7();

	UFUNCTION()
	virtual void PerformAction8();

	
	UFUNCTION()
		virtual void CancelActions() PURE_VIRTUAL(ABrainInteractiveObject::CancelActions, );

	UFUNCTION()
		bool CanUseEnergy(int32 quantity);
	UFUNCTION()
		void UseEnergy(int32 quantity);

	void PerformActionNo(int id, bool reverseAction);
};
