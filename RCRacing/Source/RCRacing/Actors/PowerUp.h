// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class RCRACING_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();
	virtual void Use(FVector direction);

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

	bool bImGoingUp = true;

	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool m_IsActive;

	void SetActive(bool isActive) { m_IsActive = isActive; }

	bool GetActive() { return m_IsActive; }

	void SetPicked(bool picked) { isPicked = picked; }

	bool isPicked = false;
};
