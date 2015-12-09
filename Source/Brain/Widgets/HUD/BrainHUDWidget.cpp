// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainHUDWidget.h"
#include "BrainEnums.h"

#define ROTATION "rotation"
#define TRANSLATION "translation"
#define SCALING "scaling"
#define SHEARING "shearing"
#define FASTFORWARDING "fastforwarding"
#define SLOWING "slowing"
#define STOPING "stop"
#define REVERSING "reverse"

void UBrainHUDWidget::SetAvailableAction(FObjectAction objectAction)
{
	if (objectAction._flags == -1)
	{
		for (int i = 0; i < 8; i++)
			_availableActions[i] = false;
	}
	else
	{
		_availableActions[0] = objectAction.GetValueForAction(EAction::ROTATE);
		_availableActions[1] = objectAction.GetValueForAction(EAction::TRANSLATE);
		_availableActions[2] = objectAction.GetValueForAction(EAction::SCALE);
		_availableActions[3] = objectAction.GetValueForAction(EAction::SHEAR);
		_availableActions[4] = objectAction.GetValueForAction(EAction::FASTFWRD);
		_availableActions[5] = objectAction.GetValueForAction(EAction::SLOW);
		_availableActions[6] = objectAction.GetValueForAction(EAction::STOP);
		_availableActions[7] = objectAction.GetValueForAction(EAction::REVERSE);
	}

	UpdateActionBar();
}

void UBrainHUDWidget::LoadActionBarTextures()
{
	
	UObjectLibrary*	actionTexturesLibrary = UObjectLibrary::CreateLibrary(UTexture2D::StaticClass(), false, true);
	actionTexturesLibrary->AddToRoot();
	

	actionTexturesLibrary->LoadAssetDataFromPath("/Game/FirstPerson/Textures/Actions");
	actionTexturesLibrary->LoadAssetsFromAssetData();

	TArray<FAssetData> AssetDatas;
	actionTexturesLibrary->GetAssetDataList(AssetDatas);

	for(FAssetData& asset : AssetDatas)
	{
		if (asset.AssetName == ROTATION)
			_actionTextures[0] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == TRANSLATION)
			_actionTextures[1] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == SCALING)
			_actionTextures[2] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == SHEARING)
			_actionTextures[3] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == FASTFORWARDING)
			_actionTextures[4] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == SLOWING)
			_actionTextures[5] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == STOPING)
			_actionTextures[6] = (Cast<UTexture2D>(asset.GetAsset()));

		if (asset.AssetName == REVERSING)
			_actionTextures[7] = (Cast<UTexture2D>(asset.GetAsset()));
	}

	actionTexturesLibrary->ClearLoaded();
	actionTexturesLibrary->ConditionalBeginDestroy();
}