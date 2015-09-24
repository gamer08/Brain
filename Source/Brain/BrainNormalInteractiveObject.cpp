// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "BrainNormalInteractiveObject.h"
#include "Components/StaticMeshComponent.h"
#include "StaticMeshResources.h"
#include "Engine.h"
//#include "BrainEnums.h"


ABrainNormalInteractiveObject::ABrainNormalInteractiveObject()
{
}

void ABrainNormalInteractiveObject::BeginPlay()
{
	Super::BeginPlay();

	int8 flags = (_canBeRotate ? EAction::ROTATE : 0) 
		       | (_canBeTranslate ? EAction::TRANSLATE : 0) 
			   | (_canBeScale ? EAction::SCALE : 0);
	_actions = FObjectAction(flags);
}

void ABrainNormalInteractiveObject::PerformAction1()
{
	if (_canBeRotate)
		ChangeRotation(1);
		//Shear(1);
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
	FMatrix shearMatrix = FMatrix(FVector(1, 0, 0), 
		                           FVector(0, 1, 1), 
								   FVector(0, 0, 1), 
								   FVector(0, 0, 0));
	
	FTransform sTrans = FTransform(shearMatrix);

	FTransform pTrans = GetTransform();	
	SetActorTransform(sTrans*pTrans);

//	TArray<FVector> vec;
//	TArray<FStaticMeshBuildVertex> vert;
//	FMatrix shearMatrix = FMatrix(FVector(1, 0, 0), 
//		                           FVector(0, 1, 1), 
//								   FVector(0, 0, 1), 
//								   FVector(0, 0, 0));
//
//	DrawDebugPoint(GetWorld(), GetActorLocation() , 20.0f, FColor::Red, true,10.0f);
//
//
//if(!IsValidLowLevel()) return;
//if(!_mesh) return;
//if(!_mesh->StaticMesh) return;
//if(!_mesh->StaticMesh->RenderData) return;
//
//	if (_mesh->StaticMesh->RenderData->LODResources.Num() > 0)
//	{
//		FPositionVertexBuffer* vBuffer = &_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer;
//		FStaticMeshVertexBuffer* verBuffer = &_mesh->StaticMesh->RenderData->LODResources[0].VertexBuffer;
//		FStaticMeshBuildVertex newVert;
//
//
//		if (vBuffer && verBuffer)
//		{
//			const int32 nbVertices = vBuffer->GetNumVertices();
//			for (int32 index = 0; index < nbVertices; index++)
//			{
//				const FVector position = GetActorLocation() + GetTransform().TransformVector(vBuffer->VertexPosition(index));
//				vec.Add(position);
//				DrawDebugPoint(GetWorld(), vec[index], 20.0f, FColor::Red, true,10.0f);
//
//				newVert = FStaticMeshBuildVertex();
//				newVert.Color = FColor::Black;
//				newVert.TangentX = verBuffer->VertexTangentX(index);
//				//newVert.TangentY = verBuffer->VertexTangentY(index);
//				newVert.TangentZ = verBuffer->VertexTangentZ(index);
//				for (int32 i = 0; i < MAX_STATIC_TEXCOORDS; i++)
//					newVert.UVs[i] = verBuffer->GetVertexUV(index, i);
//
//
//				vert.Add(newVert);
//			}
//		}
//
//		int32 numV = vec.Num();
//		for (/*FVector& v : vec*/ int32 num = 0; num < numV;num++)
//		{
//			FVector v = MatrixMultiplication(shearMatrix, vec[num]);
//			vec[num] = v;
//			vert[num].Position = v;
//
//			DrawDebugPoint(GetWorld(), vec[num], 20.0f, FColor::Red, true,10.0f);
//			DrawDebugPoint(GetWorld(), vert[num].Position, 20.0f, FColor::Yellow, true,10.0f);
//			
//		}
//
//	/*	FVector loc = GetActorLocation(); 
//		loc.Y = loc.Y + loc.Z;
//		SetActorLocation(loc);*/
//		
//		int numTextCoord = _mesh->StaticMesh->RenderData->LODResources[0].VertexBuffer.GetNumTexCoords();
//		
//		_mesh->StaticMesh->RenderData->LODResources[0].VertexBuffer.CleanUp();
//		_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer.CleanUp();
//		
//		_mesh->StaticMesh->RenderData->LODResources[0].VertexBuffer.Init(vert, numTextCoord);
//		_mesh->StaticMesh->RenderData->LODResources[0].PositionVertexBuffer.Init(vec);
//
//
//		/*FStaticMeshSection sec = _mesh->StaticMesh->RenderData->LODResources[0].Sections[0];
//		_mesh->StaticMesh->RenderData->LODResources[0].Sections.Empty();
//		FStaticMeshSection sec2 = FStaticMeshSection();
//		sec2 = sec;
//		sec2.NumTriangles = 1;
//		sec2.FirstIndex = 0;
//		sec2.MinVertexIndex = 0;
//		sec2.MaxVertexIndex = 2;
//
//		_mesh->StaticMesh->RenderData->LODResources[0].Sections.Add(sec2);*/
//
//		_mesh->MarkRenderStateDirty();
//		_mesh->MarkRenderDynamicDataDirty();
//		_mesh->MarkRenderTransformDirty();
//	}

}

FVector ABrainNormalInteractiveObject::MatrixMultiplication(FMatrix matrix, FVector vector)
{
	FVector out = FVector(0);
	out.X = (matrix.M[0][0] * vector.X) + (matrix.M[0][1] * vector.Y) + (matrix.M[0][2] * vector.Z);
	out.Y = (matrix.M[1][0] * vector.X) + (matrix.M[1][1] * vector.Y) + (matrix.M[1][2] * vector.Z);
	out.Z = (matrix.M[2][0] * vector.X) + (matrix.M[2][1] * vector.Y) + (matrix.M[2][2] * vector.Z);
	return out;
}

