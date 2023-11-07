// Fill out your copyright notice in the Description page of Project Settings.


#include "Detections/DetectableActor.h"
#include "Detections/DetectionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

ADetectableActor::ADetectableActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootMesh"));
	SetRootComponent(RootMesh);

	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetEnableGravity(false);

}

void ADetectableActor::BeginPlay()
{
	Super::BeginPlay();

	//Instantiate a dynamic version of the material.
	DynamicMaterial = UMaterialInstanceDynamic::Create(RootMesh->GetMaterial(0), this);
	RootMesh->SetMaterial(0, DynamicMaterial);

	//Fetch the DetectionActor, which should not exist in multiples.
	AActor* FindActor = UGameplayStatics::GetActorOfClass(this, ADetectionActor::StaticClass());
	DetectionActor = Cast<ADetectionActor>(FindActor);
}

// Called every frame
void ADetectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Increases or decreases the Detected value of the Dynamic Material
	//Depending on whether the actor is detected or not.
	float CurrentValue;
	if (DynamicMaterial->GetScalarParameterValue(TEXT("Detected"), CurrentValue))
	{
		bool IsDetected = RelationFlags & (uint8)(ETransformRelations::TR_DETECTED);
		float NewValue = CurrentValue + (IsDetected ? 1.0f : -1.0f) * DeltaTime * DetectedShiftSpeed;
		NewValue = FMath::Clamp(NewValue, 0.0f, 1.0f);
		DynamicMaterial->SetScalarParameterValue(TEXT("Detected"), NewValue);
	}

	//Applies force away from the detector if near it, or towards it if not near.
	if (DetectionActor)
	{
		bool IsNearby = RelationFlags & (uint8)(ETransformRelations::TR_NEAR);
		FVector Direction = DetectionActor->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
		if (IsNearby)
			Direction *= -1.0f;
		RootMesh->AddForce(Direction * 10000.0f);
	}
}

/*	Returns true if damage was backstab; deals damage either way.
*	Backstab multiplier is defined by recipient.
*/
bool ADetectableActor::TryDealBackstabDamage(float Damage, AActor* DamageCauser)
{
	FTransformRelationParams Params;
	Params.DetectionAngleInDegrees = (360.0f - BackstabAngle) / 2.0f;
	const uint8 Relations = UActorRelationsStatics::GetTransformRelations(this, DamageCauser, Params);
	bool bIsBackstab = !UActorRelationsStatics::FlagsContainRelation(Relations, ETransformRelations::TR_DETECTED);
	if (bIsBackstab)
	{
		Damage *= BackstabMultiplier;
	}
	
	//Just printing the outcome since this is not really about the damage.
	FString DamageString = GetName() + FString(" took ") + (bIsBackstab ?
		FString::SanitizeFloat(Damage) + FString(" backstab damage.") :
		FString::SanitizeFloat(Damage) + FString(" regular damage."));
	UKismetSystemLibrary::PrintString(this, DamageString, true, false, FLinearColor::Red, 5.0f);

	return bIsBackstab;
}
