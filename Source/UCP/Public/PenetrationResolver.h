#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PenetrationResolver.generated.h"

UCLASS()
class UCP_API APenetrationResolver : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Units="Centimeters"))
	double Radius = 35.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (Units="Centimeters"))
	double Height = 180.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_Pawn;

	APenetrationResolver();

	virtual void Tick(float DeltaTime) override;

private:
	void ResolvePenetration() const;
};
