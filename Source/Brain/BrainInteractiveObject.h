// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BrainInteractiveObject.generated.h"

UCLASS(Abstract)
class BRAIN_API ABrainInteractiveObject : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category=Interactive, meta = (Display = "Name"))
	FName _name;

	UPROPERTY(Visibleanywhere, Category = Interactive, meta = (Display = "Mesh"))
	UStaticMeshComponent* _mesh;

protected:
	// pas enocre utilisé va être un bitField pour les actions possible sur chaque objet
	UPROPERTY() 
	int8 _flags;
	
public:	
	ABrainInteractiveObject();

	// declaration "virtuel pure" d'unreal
	UFUNCTION()
	virtual void PerformAction1() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction1,);
	
	UFUNCTION()
	virtual void PerformAction2() PURE_VIRTUAL(ABrainInteractiveObject::PerformAction2,);

	/*Plus a venir....*/
};
