#pragma once 

#include "Brain.h"
#include "BrainCharacterSaveData.h"
#include "MyObjectSaveData.h"
#include "BrainCameraSaveData.h"
#include "BrainNIOSaveData.h"
#include "BrainTIOSaveData.h"

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
	FBrainCameraSaveData _cameraData;

	UPROPERTY()
	TMap<FString,FMyObjectSaveData> _objectSaveData;

	UPROPERTY()
	TMap<FString,FBrainNIOSaveData> _nioSaveData;

	UPROPERTY()
	TMap<FString,FBrainTIOSaveData> _tioSaveData;

	FBrainSaveData()
	{
		_levelName = FString();
		_characterData = FBrainCharacterSaveData();
		_cameraData = FBrainCameraSaveData();
		_objectSaveData.Reset();
		_nioSaveData.Reset();
		_tioSaveData.Reset();
	}
	

	void AddDataToSave(FBrainCharacterSaveData data)
	{
		_characterData = data;
	}

	void AddDataToSave(FBrainCameraSaveData data)
	{
		_cameraData = data;
	}

	void AddDataToSave(FString name, FMyObjectSaveData data)
	{
		_objectSaveData.Emplace(name, data);
	}

	void AddDataToSave(FString name, FBrainNIOSaveData data)
	{
		_nioSaveData.Emplace(name, data);
	}

	void AddDataToSave(FString name, FBrainTIOSaveData data)
	{
		_tioSaveData.Emplace(name, data);
	}

	template <typename T>
	T GetDataFromSave(FString name);

	template <> inline FBrainCharacterSaveData GetDataFromSave<FBrainCharacterSaveData>(FString name)
	{
		return _characterData;
	}

	template <> inline FBrainCameraSaveData GetDataFromSave<FBrainCameraSaveData>(FString name)
	{
		return _cameraData;
	}

	template <> inline FMyObjectSaveData GetDataFromSave<FMyObjectSaveData>(FString name)
	{
		FMyObjectSaveData data = FMyObjectSaveData();
		FMyObjectSaveData* lData = _objectSaveData.Find(name);
		
		if (lData)
			data = *lData;
		
		return data;
	}

	template <> inline FBrainNIOSaveData GetDataFromSave<FBrainNIOSaveData>(FString name)
	{
		FBrainNIOSaveData data = FBrainNIOSaveData();
		FBrainNIOSaveData* lData = _nioSaveData.Find(name);
		
		if (lData)
			data = *lData;
		
		return data;
	}

	template <> inline FBrainTIOSaveData GetDataFromSave<FBrainTIOSaveData>(FString name)
	{
		FBrainTIOSaveData data = FBrainTIOSaveData();
		FBrainTIOSaveData* lData = _tioSaveData.Find(name);
		
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
	archive << data._cameraData;
	archive << data._nioSaveData;
	archive << data._tioSaveData;

	return archive;
}
