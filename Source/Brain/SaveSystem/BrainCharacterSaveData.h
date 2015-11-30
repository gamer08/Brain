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
		int32 _energy;

	UPROPERTY()
	bool _loadFromfile;

	FBrainCharacterSaveData()
	{
		_location = FVector();
		_rotation = FRotator();

		_loadFromfile = false;

		_energy = 0;
	}

};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainCharacterSaveData& data)
{
	archive << data._location;
	archive << data._rotation;
	archive << data._loadFromfile;
	archive << data._energy;

	return archive;
}

