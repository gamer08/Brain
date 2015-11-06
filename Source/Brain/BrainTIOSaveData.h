#pragma once 

#include "Brain.h"
#include "BrainTIOSaveData.generated.h"

USTRUCT()
struct FBrainTransformSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector _currentScaleInRAD;

	FBrainTransformSaveData()
	{
		_currentScaleInRAD = FVector();
	}
};

USTRUCT()
struct FBrainTIOSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector _location;
	
	UPROPERTY()
	FRotator _rotation;

	UPROPERTY()
	FVector _scale;

	UPROPERTY()
	TArray<FBrainTransformSaveData> _transformsData;

	UPROPERTY()
	float _globalTransformationSpeed;

	UPROPERTY()
	bool _loadFromfile;

	FBrainTIOSaveData()
	{
		_location = FVector();
		_rotation = FRotator();
		_scale = FVector();
		_transformsData.Reset();
		_globalTransformationSpeed = 0.0f;
		_loadFromfile = false;
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainTIOSaveData& data)
{
	archive << data._location;
	archive << data._rotation;
	archive << data._scale;
	archive << data._transformsData;
	archive << data._globalTransformationSpeed;
	archive << data._loadFromfile;

	return archive;
}

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainTransformSaveData& data)
{
	archive << data._currentScaleInRAD;
	return archive;
}