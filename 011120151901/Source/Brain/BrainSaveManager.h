// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BrainSaveData.h"
#include "BrainSaveManager.generated.h"

/**
 * 
 */
UCLASS()
class BRAIN_API UBrainSaveManager : public UObject
{
	GENERATED_BODY()
	
public:
	
	UBrainSaveManager();
	
	bool Save();
	bool Load(FString SaveToLoad);

	TArray<FString>& GetSaveFilesName()
	{
		return _saveFilesfound;
	}
	
	template <typename T>
	T GetDataFromSave(FString name)
	{
		return _currentCachedData.GetDataFromSave(name);
	}

	template <> inline FBrainCharacterSaveData GetDataFromSave<FBrainCharacterSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FBrainCharacterSaveData>(name);
	}

	template <> inline FMyObjectSaveData GetDataFromSave<FMyObjectSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FMyObjectSaveData>(name);
	}

private:

	
	
	UPROPERTY()
	FBrainSaveData _currentCachedData;

	UPROPERTY()
	FString _savePath;

	UPROPERTY()
	FString _saveDirectory;

	UPROPERTY()
	TArray<FString> _saveFilesfound;

	void SaveNLoadData(FArchive& archive, FBrainSaveData& data);
	FString GenerateSaveFileName();

	bool LoadInternal(FString SaveToLoad);

};
