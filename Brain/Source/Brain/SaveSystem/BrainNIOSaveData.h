#pragma once 

#include "Brain.h"
#include "BrainNIOSaveData.generated.h"

USTRUCT()
struct FBrainNIOSaveData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector _location;
	
	UPROPERTY()
	FRotator _rotation;

	UPROPERTY()
	FVector _scale;

	UPROPERTY()
	float _shearFirstAxis;

	UPROPERTY()
	float _shearSecondAxis;

	UPROPERTY()
	bool _loadFromfile;

	UPROPERTY()
	int32 _countRotation;
	
	UPROPERTY()
	int32 _countTranslation;
	
	UPROPERTY()
	int32 _countScale;
	
	UPROPERTY()
	int32 _countShear;

	FBrainNIOSaveData()
	{
		_location = FVector();
		_rotation = FRotator();
		_scale = FVector();
		_shearFirstAxis = 0;
		_shearSecondAxis = 0;

		_countRotation = 0;
		_countTranslation = 0;
		_countScale = 0;
		_countShear = 0;

		_loadFromfile = false;
	}
};

FORCEINLINE FArchive &operator << (FArchive &archive, FBrainNIOSaveData& data)
{
	archive << data._location;
	archive << data._rotation;
	archive << data._scale;
	archive << data._shearFirstAxis;
	archive << data._shearSecondAxis;
	archive << data._loadFromfile;
	archive << data._countRotation;
	archive << data._countTranslation;
	archive << data._countScale;
	archive << data._countShear;

	return archive;
}