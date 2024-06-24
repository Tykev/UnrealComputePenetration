#include "PenetrationResolver.h"
#include "Engine/OverlapResult.h"

APenetrationResolver::APenetrationResolver()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APenetrationResolver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ResolvePenetration();
}

void APenetrationResolver::ResolvePenetration() const
{
	UWorld* World             = GetWorld();
	double  HalfHeight        = Height * 0.5;
	FVector ActorLocation     = GetActorLocation();
	FVector CorrectedLocation = ActorLocation;

	FCollisionShape       QueryShape  = FCollisionShape::MakeCapsule(Radius, HalfHeight);
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;

	QueryParams.AddIgnoredActor(this);

	TArray<FOverlapResult> OverlapResults;
	if(World->OverlapMultiByChannel(OverlapResults, ActorLocation, FQuat::Identity, CollisionChannel, QueryShape, QueryParams) == false)
	{
		DrawDebugCapsule(World, ActorLocation, HalfHeight, Radius, FQuat::Identity, FColor::Blue);
		return;
	}

	DrawDebugCapsule(World, ActorLocation, HalfHeight, Radius, FQuat::Identity, FColor::Red);

	for (FOverlapResult& OverlapResult : OverlapResults)
	{
		UPrimitiveComponent* OverlapComponent = OverlapResult.Component.Get();

		FMTDResult Correction;
		if (OverlapComponent->ComputePenetration(Correction, QueryShape, ActorLocation, FQuat::Identity) == true)
		{
			CorrectedLocation += Correction.Direction * Correction.Distance;
			DrawDebugLine(World, ActorLocation, CorrectedLocation, FColor::Yellow);
		}

		DrawDebugCapsule(World, CorrectedLocation, HalfHeight, Radius, FQuat::Identity, FColor::Green);
		break;
	}
}
