// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainOptionsMenuWidget.h"
#include "Widgets/Others/BrainKeyComboBoxWidget.h"

void UBrainOptionsMenuWidget::FillControlsList(UScrollBox* container)
{	
	UInputSettings* settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	if (!settings)
		return;

	TArray<FKey> ks;
	EKeys::GetAllKeys(ks);

	//filtrage des touches. On prend seulement celles qui nous intéressent
	for (FKey k : ks)
	{
		if (k.GetMenuCategory().IsEqual(FName("Key")) || k.GetMenuCategory().IsEqual(FName("Mouse")))
			_keys.Add(k);
	}
	
	FillInputKeyDisplayValues();
	FillCachedAxis();
	FillCachedActions();

	for (UBrainInputAxisIndex* axis : _axisSelectedKey)
		container->AddChild(CreateInputElement(axis));
		
	for (UBrainInputActionIndex* action : _actionsSelectedKey)
		container->AddChild(CreateInputElement(action));
} 

UHorizontalBox* UBrainOptionsMenuWidget:: CreateInputElement(IBrainInputInterface* obj)
{
	UHorizontalBox* line = NewObject<UHorizontalBox>(this);
	UTextBlock* actionName = NewObject<UTextBlock>(line);
	UBrainKeyComboBoxWidget* cb = NewObject<UBrainKeyComboBoxWidget>(line);

	actionName->Justification = ETextJustify::Center;
	actionName->SetText(FText::FromString(_inputKeyDisplayValues[obj->GetInputName()]));
	FSlateColor color = actionName->ColorAndOpacity.UseForeground();
	actionName->SetColorAndOpacity(color);
		
	for (FKey key : _keys)
		cb->AddOption(key.GetDisplayName().ToString());

	cb->SetSelectedOption(obj->GetDisplayValue().ToString());

	line->AddChild(actionName);
	line->AddChild(cb);

	UHorizontalBoxSlot* slot = Cast<UHorizontalBoxSlot>(line->GetChildAt(0)->Slot);
	if (slot)
	{
		slot->SetPadding(FMargin(0.f, 0.f, 15.f, 0.f));
			
		FSlateChildSize slotSize = FSlateChildSize();
		slotSize.SizeRule = ESlateSizeRule::Fill;
		slotSize.Value = 0.2;
		slot->SetSize(slotSize);
	}

	UHorizontalBoxSlot* slot2 = Cast<UHorizontalBoxSlot>(line->GetChildAt(1)->Slot);
	if (slot2)
	{	
		FSlateChildSize slotSize = FSlateChildSize();
		slotSize.SizeRule = ESlateSizeRule::Fill;
		slotSize.Value = 0.1;
		slot2->SetSize(slotSize);
	}

	return line;
}

void UBrainOptionsMenuWidget::SaveControls()
{
	UInputSettings* settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	
	if (!settings)
		return;

	for (auto it(_axisSelectedKey.CreateIterator()); it; it++)
	{
		//si l'input à changé on l'update
		if ((*it)->_oldInputIndex != (*it)->_newInputIndex)
		{
			settings->RemoveAxisMapping((*it)->_axis);
			const FInputAxisKeyMapping n((*it)->_axis.AxisName, _keys[(*it)->_newInputIndex],(*it)->_axis.Scale);
			settings->AddAxisMapping(n);
		}
	}

	for (auto it(_actionsSelectedKey.CreateIterator()); it; it++)
	{
		//si l'input à changé on l'update
		if ((*it)->_oldInputIndex != (*it)->_newInputIndex)
		{
			settings->RemoveActionMapping((*it)->_action);
			const FInputActionKeyMapping n((*it)->_action.ActionName, _keys[(*it)->_newInputIndex]);
			settings->AddActionMapping(n);
		}
	}

	settings->SaveKeyMappings();

	for (TObjectIterator<UPlayerInput> it; it; ++it)
		it->ForceRebuildingKeyMaps(true);
}

//enregistre les touches de déplacement configurables dans un ordre precis
void UBrainOptionsMenuWidget::FillCachedAxis()
{
	UInputSettings* settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	AddAxisToList(settings, FName("MoveForward"));
	AddAxisToList(settings, FName("MoveBackward"));
	AddAxisToList(settings, FName("MoveRight"));
	AddAxisToList(settings, FName("MoveLeft"));
}

//enregistre les touches d'actions configurables dans un ordre precis
void UBrainOptionsMenuWidget::FillCachedActions()
{
	UInputSettings* settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

	AddActionToList(settings, FName("Jump"));
	AddActionToList(settings, FName("PerformActionOnObject1"));
	AddActionToList(settings, FName("PerformActionOnObject2"));
	AddActionToList(settings, FName("PerformActionOnObject3"));
	AddActionToList(settings, FName("PerformActionOnObject4"));
	AddActionToList(settings, FName("PerformActionOnObject5"));
	AddActionToList(settings, FName("PerformActionOnObject6"));
	AddActionToList(settings, FName("PerformActionOnObject7"));
	AddActionToList(settings, FName("PerformActionOnObject8"));
}

void UBrainOptionsMenuWidget::AddAxisToList(UInputSettings* settings, FName name)
{
	FInputAxisKeyMapping ax = FInputAxisKeyMapping();
	UBrainInputAxisIndex* inputAxis;

	ax = *settings->AxisMappings.FindByPredicate([&](FInputAxisKeyMapping axis){return axis.AxisName.IsEqual(name);});
	inputAxis = NewObject<UBrainInputAxisIndex>(this);
	inputAxis->InitData(ax, _keys.IndexOfByKey(ax.Key), 0);
	_axisSelectedKey.Add(inputAxis);
}

void UBrainOptionsMenuWidget::AddActionToList(UInputSettings* settings, FName name)
{
	FInputActionKeyMapping ac = FInputActionKeyMapping();
	UBrainInputActionIndex* inputAction;

	ac = *settings->ActionMappings.FindByPredicate([&](FInputActionKeyMapping action){return action.ActionName.IsEqual(name); });
	inputAction = NewObject<UBrainInputActionIndex>(this);
	inputAction->InitData(ac, _keys.IndexOfByKey(ac.Key), 0);
	_actionsSelectedKey.Add(inputAction);
}

void UBrainOptionsMenuWidget::FillInputKeyDisplayValues()
{
	_inputKeyDisplayValues.Emplace("Jump", "Sauter");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject1", "Rotation positive / Accelerer");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject2", "Rotation negative / Ralentir");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject3", "Translation Positive / Arreter");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject4", "Translation negative / Inverser");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject5", "Mise a l'echelle positive");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject6", "Mise a l'echelle negative");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject7", "Cisaillement positif");
	_inputKeyDisplayValues.Emplace("PerformActionOnObject8", "Cisaillement negatif");
	_inputKeyDisplayValues.Emplace("MoveForward", "Deplacement en avant");
	_inputKeyDisplayValues.Emplace("MoveBackward", "Deplacement en arriere");
	_inputKeyDisplayValues.Emplace("MoveLeft", "Deplacement sur la gauche");
	_inputKeyDisplayValues.Emplace("MoveRight", "Deplacement sur la droite");
}

