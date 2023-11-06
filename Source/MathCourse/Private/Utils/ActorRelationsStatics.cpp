// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/ActorRelationsStatics.h"

bool UActorRelationsStatics::IsInFrontOf(AActor* Actor, AActor* OtherActor)
{
	const FVector VectorInLocal = Actor->GetActorTransform().InverseTransformPosition(OtherActor->GetActorLocation());
	return VectorInLocal.X > 0;
}

bool UActorRelationsStatics::IsRightOf(AActor* Actor, AActor* OtherActor)
{
	const FVector VectorInLocal = Actor->GetActorTransform().InverseTransformPosition(OtherActor->GetActorLocation());
	return VectorInLocal.Y > 0;
}

bool UActorRelationsStatics::IsAbove(AActor* Actor, AActor* OtherActor)
{
	const FVector VectorInLocal = Actor->GetActorTransform().InverseTransformPosition(OtherActor->GetActorLocation());
	return VectorInLocal.Z > 0;
}

uint8 UActorRelationsStatics::GetTransformRelations(AActor* Actor, AActor* OtherActor, FTransformRelationParams& Params)
{
	uint8 Flags;
	if (IsInFrontOf(Actor, OtherActor))
	{
		Flags = Flags |= (uint8)(ETransformRelations::TR_FRONT);
	}
	if (IsRightOf(Actor, OtherActor))
	{
		Flags = Flags |= (uint8)(ETransformRelations::TR_RIGHT);
	}
	if (IsAbove(Actor, OtherActor))
	{
		Flags = Flags |= (uint8)(ETransformRelations::TR_ABOVE);
	}
	if (Params.NearbyDistance > FVector::Distance(Actor->GetActorLocation(), OtherActor->GetActorLocation()))
	{
		Flags = Flags |= (uint8)(ETransformRelations::TR_NEAR);
	}
	if (Actor->GetActorForwardVector().Dot(OtherActor->GetActorForwardVector()) > 0)
	{
		Flags = Flags |= (uint8)(ETransformRelations::TR_FACINGSAME);
	}
	return 0;
}