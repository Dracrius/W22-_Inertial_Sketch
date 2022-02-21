// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class APowerUp;
class UBoxComponent;
UCLASS()
class RCRACING_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupBox")
		UBoxComponent* PickupBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickupMesh")
		UStaticMeshComponent* PickupMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bImGoingUp = true;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		TSubclassOf<APowerUp> PowerupClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
