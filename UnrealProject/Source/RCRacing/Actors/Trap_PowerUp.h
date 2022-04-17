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
#include "Trap_PowerUp.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class RCRACING_API ATrap_PowerUp : public APowerUp
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ATrap_PowerUp();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//switch
	bool bImGoingUp = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Called on space bar by the player
	virtual void Use(FVector direction, FVector SpawnPosition) override;
};
