// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "BrainSaveData.h"
#include "BrainSaveManager.generated.h"

UCLASS()
class BRAIN_API UBrainSaveManager : public UObject
{
	GENERATED_BODY()
	
public:
	
	UBrainSaveManager();
	
	bool Save(FString saveName);
	bool Load(FString SaveToLoad);

	TArray<FString> GetSaveFilesName();

	template <typename T>
	T GetDataFromSave(FString name)
	{
		return _currentCachedData.GetDataFromSave(name);
	}

	template <> inline FBrainCharacterSaveData GetDataFromSave<FBrainCharacterSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FBrainCharacterSaveData>(name);
	}

	template <> inline FBrainCameraSaveData GetDataFromSave<FBrainCameraSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FBrainCameraSaveData>(name);
	}
	
	template <> inline FBrainNIOSaveData GetDataFromSave<FBrainNIOSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FBrainNIOSaveData>(name);
	}

	template <> inline FBrainTIOSaveData GetDataFromSave<FBrainTIOSaveData>(FString name)
	{
		return _currentCachedData.GetDataFromSave<FBrainTIOSaveData>(name);
	}

	void FlushCachedSaveData();

private:

	UPROPERTY()
	FBrainSaveData _currentCachedData;

	UPROPERTY()
	FString _saveDirectory;

	void SaveNLoadData(FArchive& archive, FBrainSaveData& data);
	FString GenerateSaveFileName();

	bool LoadInternal(FString SaveToLoad);
};