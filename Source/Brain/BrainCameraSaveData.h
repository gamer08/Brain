#pragma once 

#include "Brain.h"
#include "BrainCameraSaveData.generated.h"

USTRUCT()
struct FBrainCameraSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FRotator _rotation;

	UPROPERTY()
	bool _loadFromfile;

	FBrainCameraSaveData()
	{
		_rotation = FRotator();
		_loadFromfile = false;
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainCameraSaveData& data)
{
	archive << data._rotation;
	archive << data._loadFromfile;

	return archive;
}