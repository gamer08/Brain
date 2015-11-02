#pragma once 

#include "Brain.h"
#include "BrainCharacterSaveData.h"
#include "MyObjectSaveData.h"

#include "BrainSaveData.generated.h"

USTRUCT()
struct FBrainSaveData
{
	GENERATED_USTRUCT_BODY()

public:
	
	UPROPERTY()
	FString _levelName;
	
	UPROPERTY()
	FBrainCharacterSaveData _characterData;

	UPROPERTY()
	TMap<FString,FMyObjectSaveData> _objectSaveData;

	FBrainSaveData()
	{
		_levelName = FString();
		_characterData = FBrainCharacterSaveData();
		_objectSaveData.Reset();
	}
	

	void AddDataToSave(FBrainCharacterSaveData data)
	{
		_characterData = data;
	}

	void AddDataToSave(FString name, FMyObjectSaveData data)
	{
		_objectSaveData.Emplace(name, data);
	}

	template <typename T>
	T GetDataFromSave(FString name);

	template <> inline FBrainCharacterSaveData GetDataFromSave<FBrainCharacterSaveData>(FString name)
	{
		return _characterData;
	}

	template <> inline FMyObjectSaveData GetDataFromSave<FMyObjectSaveData>(FString name)
	{
		FMyObjectSaveData data = FMyObjectSaveData();
		FMyObjectSaveData* lData = _objectSaveData.Find(name);
		
		if (lData)
			data = *lData;
		
		return data;
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainSaveData& data)
{
	archive << data._levelName;
	archive << data._characterData;
	archive << data._objectSaveData;

	return archive;
}
