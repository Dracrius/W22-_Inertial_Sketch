// Fill out your copyright notice in the Description page of Project Settings.

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
	ATrap_PowerUp();
	virtual void Use(FVector direction) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bImGoingUp = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};