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
	TR_FACINGSAME = 1 << 4	UMETA(DisplayName = "Facing Same")
};
ENUM_CLASS_FLAGS(ETransformRelations);

USTRUCT(BlueprintType)
struct FTransformRelationParams
{
	GENERATED_BODY()

public:
	float NearbyDistance;
};

/**
 * 
 */
UCLASS()
class MATHCOURSE_API UActorRelationsStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static bool IsInFrontOf(AActor* Actor, AActor* OtherActor);
	static bool IsRightOf(AActor* Actor, AActor* OtherActor);
	static bool IsAbove(AActor* Actor, AActor* OtherActor);

	static uint8 GetTransformRelations(AActor* Actor, AActor* OtherActor, FTransformRelationParams& Params);
	
};
