#pragma once 

#include "Brain.h"
#include "BrainCharacterSaveData.generated.h"

USTRUCT()
struct FBrainCharacterSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector _location;

	UPROPERTY()
	FRotator _rotation;

	UPROPERTY()
	bool _loadFromfile;

	FBrainCharacterSaveData()
	{
		_location = FVector();
		_rotation = FRotator();

		_loadFromfile = false;
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainCharacterSaveData& data)
{
	archive << data._location;
	archive << data._rotation;
	archive << data._loadFromfile;

	return archive;
}