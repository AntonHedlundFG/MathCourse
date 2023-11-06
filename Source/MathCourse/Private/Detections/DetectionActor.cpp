// Fill out your copyright notice in the Description page of Project Settings.


#include "Detections/DetectionActor.h"
#include "Detections/DetectableActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

ADetectionActor::ADetectionActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootMesh"));
	SetRootComponent(RootMesh);
}

void ADetectionActor::BeginPlay()
{
	Super::BeginPlay();
	
	//Fetch all ADetectableActors and store them in an array.
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(
		this,
		ADetectableActor::StaticClass(),
		OutActors);
	for (AActor* Actor : OutActors)
	{
		if (ADetectableActor* Detectable = Cast<ADetectableActor>(Actor))
			DetectableActors.Add(Detectable);
	}

}

void ADetectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (ADetectableActor* Detectable : DetectableActors)
	{
		uint8 Flags = UActorRelationsStatics::GetTransformRelations(this, Detectable, TransformRelationParams);
		Detectable->SetRelationFlags(Flags);
	}
}

