// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainSaveManager.h"
#include "BrainSaveInterface.h"
#include "EngineUtils.h"
#include <cstdlib>
#include <string>
#include <ctime>

UBrainSaveManager::UBrainSaveManager()
{
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		_isASaveLoaded = false;

		std::string userProfile, saveDirectory;
		userProfile.clear();
		saveDirectory.clear();
		
		userProfile = std::getenv("USERPROFILE");
		saveDirectory = "\\Documents\\Brain\\Saves";
		userProfile.append(saveDirectory);
		
		_saveDirectory = FString(userProfile.c_str());

		if (!FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*_saveDirectory))
			FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*_saveDirectory);
	}
}

TArray<FString> UBrainSaveManager::GetSaveFilesName()
{
	TArray<FString> saveFilesfound;
	
	FString pathNFilter = _saveDirectory + "/" + "*.save";
	IFileManager::Get().FindFiles(saveFilesfound, *pathNFilter, true, true);

	return saveFilesfound;
}

void UBrainSaveManager::SaveNLoadData(FArchive& archive, FBrainSaveData& data)
{
	archive << data;
}

bool UBrainSaveManager::Save(FString saveName)
{
	bool saveSuccessfull = false;

	FString saveFileName;

	if (saveName.IsEmpty())
		saveFileName = GenerateSaveFileName();
	else
		saveFileName = saveName;

	FString saveFilePath = _saveDirectory + "\\" + saveFileName;
	
	FBrainSaveData saveData = FBrainSaveData();

	UWorld* world = GetOuter()->GetWorld();

	if (world)
	{
		saveData._levelName = world->GetName();

		for (TObjectIterator<UObject> obj; obj; ++obj)
		{
			if (obj 
				&& obj->GetClass()->ImplementsInterface(UBrainSaveInterface::StaticClass())
				&& !obj->HasAnyFlags( RF_ClassDefaultObject | RF_ArchetypeObject )
				&& !obj->GetOuter()->HasAnyFlags( RF_ClassDefaultObject | RF_ArchetypeObject ))
			{
				Cast<IBrainSaveInterface>(*obj)->Save(saveData);
			}	
		}

		FBufferArchive toSave = FBufferArchive();

		SaveNLoadData(toSave, saveData);

		if (toSave.Num() <= 0)
			return false;

		if (FFileHelper::SaveArrayToFile(toSave, *saveFilePath))
			saveSuccessfull = true;

		toSave.FlushCache();
		toSave.Empty();
		toSave.Close();
	}
	return saveSuccessfull;
}

bool UBrainSaveManager::Load(FString SaveToLoad)
{
	bool loadSuccessfull = false;

	_isASaveLoaded = LoadInternal(SaveToLoad);

	if (_isASaveLoaded)
	{
		UWorld* world = GetOuter()->GetWorld();
		if (world)
		{
			FName name = FName(*_currentCachedData._levelName);
			loadSuccessfull = true;
			UGameplayStatics::OpenLevel(world, FName(*_currentCachedData._levelName));
		}
	}

	return loadSuccessfull;
}

bool UBrainSaveManager::LoadInternal(FString SaveToLoad)
{
	bool loadSuccessfull = false;

	TArray<uint8> binaryData;

	_currentCachedData = FBrainSaveData();

	FString saveFilePath = _saveDirectory + "\\" + SaveToLoad;

	if ((FFileHelper::LoadFileToArray(binaryData, *saveFilePath)) && (binaryData.Num() >0))
	{
		FMemoryReader toData = FMemoryReader(binaryData, true);
		toData.Seek(0);
		SaveNLoadData(toData, _currentCachedData);

		toData.FlushCache();
		binaryData.Empty();
		
		loadSuccessfull = true;
	}

	return loadSuccessfull;
}

FString UBrainSaveManager::GenerateSaveFileName()
{
	time_t nowT = time(0);
	struct tm* now = localtime(&nowT);
	char buffer[100];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %Hh%Mm%S", now);
	
	return FString("BRN ").Append(buffer).Append(".save"); 
}

void UBrainSaveManager::FlushCachedSaveData()
{
	_isASaveLoaded = false;
	_currentCachedData = FBrainSaveData();
}