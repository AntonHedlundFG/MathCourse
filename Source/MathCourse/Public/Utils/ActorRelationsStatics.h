// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorRelationsStatics.generated.h"

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ETransformRelations : uint8
{
	TR_NULL = 0				UMETA(Hidden),
	TR_FRONT = 1 << 0		UMETA(DisplayName = "In Front"),
	TR_RIGHT = 1 << 1		UMETA(DisplayName = "To the Right"),
	TR_ABOVE = 1 << 2		UMETA(DisplayName = "Above"),
	TR_NEAR = 1 << 3		UMETA(DisplayName = "Near"),
	TR_FACINGSAME = 1 << 4	UMETA(DisplayName = "Facing Same"),
	TR_DETECTED = 1 << 5	UMETA(DisplayName = "Detected"),
	TR_MAX = 1 << 6			UMETA(Hidden)
};
ENUM_CLASS_FLAGS(ETransformRelations);

USTRUCT(BlueprintType)
struct FTransformRelationParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	float NearbyDistance = 500.0f;
	UPROPERTY(EditAnywhere) float DetectionAngleInDegrees = 45.0f;
};

/**
 * 
 */
UCLASS()
class MATHCOURSE_API UActorRelationsStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable) static bool IsInFrontOf(AActor* Actor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable) static bool IsRightOf(AActor* Actor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable) static bool IsAbove(AActor* Actor, AActor* OtherActor);
	UFUNCTION(BlueprintCallable) static bool FacingSameDirection(AActor* Actor, AActor* OtherActor);
	
	//Gives 0 if OtherActor is directly in fromt of Actor (using Forward vector)
	UFUNCTION(BlueprintCallable)
	static float AngleFromForward(AActor* Actor, AActor* OtherActor, bool UsingDegrees = false);
	
	UFUNCTION(BlueprintCallable)
	static uint8 GetTransformRelations(AActor* Actor, AActor* OtherActor, FTransformRelationParams& Params);
	
	UFUNCTION(BlueprintCallable)
	static bool FlagsContainRelation(uint8 Flags, ETransformRelations Relation);
};
