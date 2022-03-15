// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "Firework_PowerUp.generated.h"

class USphereComponent;
class UStaticMeshComponent;
/**
 *
 */
UCLASS()
class RCRACING_API AFirework_PowerUp : public APowerUp
{
	GENERATED_BODY()
public:
	AFirework_PowerUp();
	virtual void Use(FVector direction) override;
	void Explode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "BombActor")
		UParticleSystem* ExplosionTemplate;

	bool isFired = false;

};