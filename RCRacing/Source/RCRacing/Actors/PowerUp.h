// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

class UBoxComponent;
UCLASS()
class RCRACING_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUpBox")
		UBoxComponent* PowerupBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUpBox")
		UStaticMeshComponent* PowerupMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RandomizePowerup();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FreezePowerUp();
	void TrapPowerUp();
	void BowlingBallPowerUp();
	void FireworkPowerUp();

};
