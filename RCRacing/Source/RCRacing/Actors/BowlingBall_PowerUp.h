/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.1
Author : Antoine Plouffe
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "BowlingBall_PowerUp.generated.h"

class USphereComponent;
class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class RCRACING_API ABowlingBall_PowerUp : public APowerUp
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABowlingBall_PowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//starts when the power up collision sphere hits a vehicle
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;

	//Called on space bar by the player
	virtual void Use(FVector direction) override;

	//Called when OnHit is triggered by a vehicle
	void Explode();

	//Explosion visual
	UPROPERTY(EditAnywhere, Category = "BombActor")
		UParticleSystem* ExplosionTemplate;
};
