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

bool UActorRelationsStatics::FacingSameDirection(AActor* Actor, AActor* OtherActor)
{
	return Actor->GetActorForwardVector().Dot(OtherActor->GetActorForwardVector()) > 0;
}
float UActorRelationsStatics::AngleFromForward(AActor* Actor, AActor* OtherActor, bool UsingDegrees)
{
	const float Dot = Actor->GetActorForwardVector().Dot((OtherActor->GetActorLocation() - Actor->GetActorLocation()).GetSafeNormal());
	return UsingDegrees ? FMath::RadiansToDegrees(FMath::Acos(Dot)) : FMath::Acos(Dot);
}

uint8 UActorRelationsStatics::GetTransformRelations(AActor* Actor, AActor* OtherActor, FTransformRelationParams& Params)
{
	uint8 Flags;
	if (IsInFrontOf(Actor, OtherActor))
	{
		Flags |= (uint8)(ETransformRelations::TR_FRONT);
	}
	if (IsRightOf(Actor, OtherActor))
	{
		Flags |= (uint8)(ETransformRelations::TR_RIGHT);
	}
	if (IsAbove(Actor, OtherActor))
	{
		Flags |= (uint8)(ETransformRelations::TR_ABOVE);
	}
	if (Params.NearbyDistance > FVector::Distance(Actor->GetActorLocation(), OtherActor->GetActorLocation()))
	{
		Flags |= (uint8)(ETransformRelations::TR_NEAR);
	}
	if (FacingSameDirection(Actor, OtherActor))
	{
		Flags |= (uint8)(ETransformRelations::TR_FACINGSAME);
	}
	if (AngleFromForward(Actor, OtherActor, true) <= Params.DetectionAngleInDegrees)
	{
		Flags |= (uint8)(ETransformRelations::TR_DETECTED);
	}
	return Flags;
}