// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"
#include "Components/StaticMeshComponent.h"
#include "StaticMeshResources.h"
#include "Engine.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{
}

void ABrainNormalInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	int8 flags = (_canBeRotate ? EAction::ROTATE : 0)
		| (_canBeTranslate ? EAction::TRANSLATE : 0)
		| (_canBeScale ? EAction::SCALE : 0)
		| (_canBeShear ? EAction::SHEAR : 0);
	_actions = FObjectAction(flags);
}

void ABrainNormalInteractiveObject::PerformAction1()
{
	if (_canBeRotate)
		ChangeRotation(1);
}

void ABrainNormalInteractiveObject::PerformAction2()
{
	if (_canBeRotate)
		ChangeRotation(-1);
}

void ABrainNormalInteractiveObject::PerformAction3()
{
	if (_canBeTranslate)
		ChangePosition(1);
}

void ABrainNormalInteractiveObject::PerformAction4()
{
	if (_canBeTranslate)
		ChangePosition(-1);
}

void ABrainNormalInteractiveObject::PerformAction5()
{
	if (_canBeScale)
		ChangeScale(1);
}

void ABrainNormalInteractiveObject::PerformAction6()
{
	if (_canBeScale)
		ChangeScale(-1);
}

void ABrainNormalInteractiveObject::PerformAction7()
{
	if (_canBeShear)
		Shear(1);
}

void ABrainNormalInteractiveObject::PerformAction8()
{
	if (_canBeShear)
		Shear(-1);
}

void ABrainNormalInteractiveObject::ChangeRotation(int32 orientation)
{
	FRotator rotation = GetActorRotation();
	SetActorRotation(rotation + (orientation * _rotationToApply));
}

void ABrainNormalInteractiveObject::ChangePosition(int32 orientation)
{
	FVector location = GetActorLocation();
	SetActorLocation(location + (orientation * _translationToApply));
}

void ABrainNormalInteractiveObject::ChangeScale(int32 orientation)
{
	FVector newScale = FVector(0);
	
	if (CanBeRescale(orientation, newScale))
		SetActorScale3D(newScale);
}

bool ABrainNormalInteractiveObject::CanBeRescale(int32 orientation, FVector& newScale)
{
	newScale = (GetActorScale3D() + (orientation * _scaleToApply));
	
	if ((newScale.Size() >= _minScale.Size()) && (newScale.Size() <= _maxScale.Size()))
		return true;
	else
		return false;

}

void ABrainNormalInteractiveObject::Shear(int32 orientation)
{
	/*FMatrix shearMatrix = FMatrix(FVector(1, 0, 0), 
		                           FVector(0, 1, 1), 
								   FVector(0, 0, 1), 
								   FVector(0, 0, 0));
	
	FTransform sTrans = FTransform(shearMatrix);

	FTransform pTrans = GetTransform();	
	SetActorTransform(sTrans*pTrans);*/

	TArray<FVector> vec;
	FMatrix shearMatrix = FMatrix(FVector(1, 0, 0), 
		                           FVector(0, 1, 0.1), 
								   FVector(0, 0, 1), 
								   FVector(0, 0, 0));

if(!IsValidLowLevel()) return;
if(!_mesh) return;
if(!_mesh->StaticMesh) return;
if(!_mesh->StaticMesh->RenderData) return;

	if (_mesh->StaticMesh->RenderData->LODResources.Num() > 0)
	{
		FPositionVertexBuffer* vBuffer = &_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer;

		if (vBuffer)
		{
			const int32 nbVertices = vBuffer->GetNumVertices();
			for (int32 index = 0; index < nbVertices; index++)
			{
				const FVector position = GetActorLocation() + GetTransform().TransformVector(vBuffer->VertexPosition(index));
				vec.Add(position);
			}
		}

		for (FVector& v : vec)
			v = MatrixMultiplication(shearMatrix, v);
		
		_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer.Init(vec);
		_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer.InitRHI();

		_mesh->MarkRenderStateDirty();
		_mesh->MarkRenderDynamicDataDirty();
		_mesh->MarkRenderTransformDirty();
	}
}

FVector ABrainNormalInteractiveObject::MatrixMultiplication(FMatrix matrix, FVector vector)
{
	FVector out = FVector(0);
	out.X = (matrix.M[0][0] * vector.X) + (matrix.M[0][1] * vector.Y) + (matrix.M[0][2] * vector.Z);
	out.Y = (matrix.M[1][0] * vector.X) + (matrix.M[1][1] * vector.Y) + (matrix.M[1][2] * vector.Z);
	out.Z = (matrix.M[2][0] * vector.X) + (matrix.M[2][1] * vector.Y) + (matrix.M[2][2] * vector.Z);
	return out;
}

