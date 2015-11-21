// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Object.h"
#include "BrainInputInterface.h"
#include "BrainOptionsMenuWidget.generated.h"

UCLASS(BlueprintType)
class UBrainInputAxisIndex : public UObject, public IBrainInputInterface
{
	GENERATED_BODY()

public:
	
	UBrainInputAxisIndex()
	{}
	
	FName GetInputName()
	{
		return _axis.AxisName;
	}

	FText GetDisplayValue()
	{
		return _axis.Key.GetDisplayName();
	}

	void InitData(FInputAxisKeyMapping axis, int32 oldInputIndex, int32 newInputIndex)
	{
		_axis = axis;
		_oldInputIndex = oldInputIndex;
		_newInputIndex = newInputIndex;
	}
	
	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	FInputAxisKeyMapping _axis;
	
	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	int32 _oldInputIndex;

	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	int32 _newInputIndex;
};

UCLASS(BlueprintType)
class UBrainInputActionIndex : public UObject, public IBrainInputInterface
{
	GENERATED_BODY()

public:
	
	UBrainInputActionIndex()
	{}
	
	FName GetInputName()
	{
		return _action.ActionName;
	}

	FText GetDisplayValue()
	{
		return _action.Key.GetDisplayName();
	}

	void InitData(FInputActionKeyMapping action, int32 oldInputIndex, int32 newInputIndex)
	{
		_action = action;
		_oldInputIndex = oldInputIndex;
		_newInputIndex = newInputIndex;
	}
	
	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	FInputActionKeyMapping _action;
	
	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	int32 _oldInputIndex;

	UPROPERTY(BlueprintReadWrite, Category = "InputIndex")
	int32 _newInputIndex;
};

UCLASS()
class BRAIN_API UBrainOptionsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TMap<FName, FString> _inputKeyDisplayValues;

	UPROPERTY()
	TArray<FKey> _keys;

	void FillInputKeyDisplayValues();
	void FillCachedAxis();
	void FillCachedActions();
	void AddAxisToList(UInputSettings* settings, FName name);
	void AddActionToList(UInputSettings* settings, FName name);
	UHorizontalBox* CreateInputElement(IBrainInputInterface* obj);

public:

	UPROPERTY(BlueprintReadWrite, Category = "Controls")
	TArray<UBrainInputAxisIndex*> _axisSelectedKey;

	UPROPERTY(BlueprintReadWrite, Category = "Controls")
	TArray<UBrainInputActionIndex*> _actionsSelectedKey;
	
	UFUNCTION(BlueprintCallable, Category = "Controls")
	void FillControlsList(UScrollBox* container);	

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SaveControls();	
};
