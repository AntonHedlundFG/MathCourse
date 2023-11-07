// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utils/ActorRelationsStatics.h"
#include "DetectableActor.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class ADetectionActor;

/** This class functions only when a DetectionActor exists in the level
*	which can supply values to its RelationFlags.
*/
UCLASS()
class MATHCOURSE_API ADetectableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADetectableActor();
	virtual void Tick(float DeltaTime) override;

	//	This is called by a DetectionActor each frame.
	UFUNCTION()
	void SetRelationFlags(uint8 NewFlags) { RelationFlags = NewFlags; }

	/*	Returns true if damage was backstab; deals damage either way.
	*	Backstab multiplier is defined by recipient.
	*/
	UFUNCTION(BlueprintCallable)
	bool TryDealBackstabDamage(float Damage, AActor* DamageCauser);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> RootMesh;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ADetectionActor> DetectionActor;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "/Script/MathCourse.ETransformRelations"))
	uint8 RelationFlags;	

	/*	Sets the speed of the visibility shift that depends on whether the DetectionActor
	*	Can see this actor or not.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DetectedShiftSpeed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackstabMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackstabAngle = 120.0f;

};
