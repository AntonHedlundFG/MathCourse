// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/ActorRelationsStatics.h"
#include "DetectableActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MATHCOURSE_API ADetectableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADetectableActor();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetRelationFlags(uint8 NewFlags) { RelationFlags = NewFlags; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "/Script/MathCourse.ETransformRelations"))
	uint8 RelationFlags;	

};
