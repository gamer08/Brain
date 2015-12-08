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

protected:
	UPROPERTY(Visibleanywhere, Category = Interactive, meta = (DisplayName = "Mesh"))
	UStaticMeshComponent* _mesh;
	
	UPROPERTY()
	FObjectAction _actions;

	UPROPERTY()
	UMaterialInstanceDynamic* _materialInstance;

	UPROPERTY()
	FLinearColor _defaultColor;

	UPROPERTY(EditAnywhere, Category = Interactive, meta = (DisplayName = "Selection Color"))
	bool _allowChangeColorOnHover;

	UPROPERTY(EditAnywhere, Category = Interactive, meta = (DisplayName = "Selection Color"))
	FLinearColor _selectionColor;

	void BeginPlay() override;

public:	
	ABrainInteractiveObject();

	const FObjectAction GetAvailableActions()
	{
		return _actions;
	}

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
	bool CanUseEnergy(int32 quantity);
	
	UFUNCTION()
	void UseEnergy(int32 quantity);

	void ApplySelectionColor();

	void ResetMaterialColor();
};
