// Fill out your copyright notice in the Description page of Project Settings.


#include "Detections/DetectableActor.h"
#include "Detections/DetectionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"


// Sets default values
ADetectableActor::ADetectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootMesh"));
	SetRootComponent(RootMesh);

	RootMesh->SetSimulatePhysics(true);
	RootMesh->SetEnableGravity(false);

}

// Called when the game starts or when spawned
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

