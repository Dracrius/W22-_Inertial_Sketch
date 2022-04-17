/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4
*/
#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "Freeze_PowerUp.generated.h"


class USphereComponent;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class RCRACING_API AFreeze_PowerUp : public APowerUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFreeze_PowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called on space bar by the player
	virtual void Use(FVector direction, FVector SpawnPosition) override;

	//Freeze Radius
	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius = 500.0f;
};
