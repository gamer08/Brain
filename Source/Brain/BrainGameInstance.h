// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "SaveSystem/BrainSaveManager.h"
#include "BrainGameInstance.generated.h"

/**
 * Classe singleton possédant le singleton SaveManager
 */
UCLASS()
class BRAIN_API UBrainGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	void Init() override;
	
	UPROPERTY()
	UBrainSaveManager* _saveManager;

public:
	UBrainGameInstance();

	inline UBrainSaveManager* GetSaveManager() const
	{
		return _saveManager;
	}
	
};
