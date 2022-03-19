// Fill out your copyright notice in the Description page of Project Settings.
//Version: 0.1
//Author : Antoine Plouffe
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
	virtual void Use(FVector direction) override;

	//Freeze Radius
	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceRadius = 500.0f;
};
