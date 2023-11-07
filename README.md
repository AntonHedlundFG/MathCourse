# 3D Mathematics Course - FutureGames

## [Exercise 1: State and Context](https://github.com/AntonHedlundFG/MathCourse/releases/tag/Exercise-1-State-and-Context)

### [UActorRelationStatics](/Source/MathCourse/Public/Utils/ActorRelationsStatics.h)
A simple helper library for determining transform relationships between actors. It has a few functions determining simple relationships like "IsAbove". It can also generate a full list of properties using the ETransformRelations bitflag:
```
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ETransformRelations : uint8
{
	TR_NULL = 0			UMETA(Hidden),
	TR_FRONT = 1 << 0		UMETA(DisplayName = "In Front"),
	TR_RIGHT = 1 << 1		UMETA(DisplayName = "To the Right"),
	TR_ABOVE = 1 << 2		UMETA(DisplayName = "Above"),
	TR_NEAR = 1 << 3		UMETA(DisplayName = "Near"),
	TR_FACINGSAME = 1 << 4	        UMETA(DisplayName = "Facing Same"),
	TR_DETECTED = 1 << 5	        UMETA(DisplayName = "Detected"),
	TR_MAX = 1 << 6			UMETA(Hidden)
};
```

### [DetectionActor](/Source/MathCourse/Public/Detections/DetectionActor.h) and [DetectableActor](/Source/MathCourse/Public/Detections/DetectableActor.h)
Two simple Actor types used to test interactions based on the transform relationships defined in ActorRelationsStatics.h.

DetectionActor should be used as a singleton and provides relational data each Tick to each DetectableActor in the level.

DetectableActor reacts to the relational data provided by the DetectionActor in multiple ways. It shifts from visible to invisible depending on the TR_DETECTED flag, it moves away from or towards the DetectionActor depending on the TR_NEAR flag, and it has a TryDealBackstabDamage function that uses the helper library to determine if the actor causing the damage is located within a backstabable area, as defined by its BackstabAngle property.
