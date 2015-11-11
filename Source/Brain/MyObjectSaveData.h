#pragma once 

#include "Brain.h"
#include "MyObjectSaveData.generated.h"

USTRUCT()
struct FMyObjectSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float _number;

	UPROPERTY()
	bool _loadFromfile;

	FMyObjectSaveData()
	{
		_number = 0.0f;
		_loadFromfile = false;
	}

};

FORCEINLINE FArchive &operator << (FArchive &archive, FMyObjectSaveData& data)
{
	archive << data._number;
	archive << data._loadFromfile;

	return archive;
}