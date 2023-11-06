// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/ActorRelationsStatics.h"
#include "DetectionActor.generated.h"

class UStaticMeshComponent;
class ADetectableActor;

UCLASS()
class MATHCOURSE_API ADetectionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADetectionActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ADetectableActor*> DetectableActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransformRelationParams TransformRelationParams;
};
