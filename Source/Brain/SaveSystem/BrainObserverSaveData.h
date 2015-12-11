#pragma once 

#include "Brain.h"
#include "BrainObserverSaveData.generated.h"

USTRUCT()
struct FBrainObserverSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	bool _state;

	UPROPERTY()
	TMap<FString, int8> _subjects;

	UPROPERTY()
	bool _loadFromfile;

	FBrainObserverSaveData()
	{
		_state = false;
		_loadFromfile = false;
		_subjects.Reset();
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainObserverSaveData& data)
{
	archive << data._state;
	archive << data._subjects;
	archive << data._loadFromfile;

	return archive;
}