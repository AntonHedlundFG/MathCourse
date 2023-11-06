// Fill out your copyright notice in the Description page of Project Settings.


#include "Detections/DetectableActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ADetectableActor::ADetectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("RootMesh"));
	SetRootComponent(RootMesh);


}

// Called when the game starts or when spawned
void ADetectableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADetectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

