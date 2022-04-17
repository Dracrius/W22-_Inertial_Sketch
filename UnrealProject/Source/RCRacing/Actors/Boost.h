/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boost.generated.h"

class USphereComponent;
UCLASS()
class RCRACING_API ABoost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoost();

	//Collision sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoostSphere")
		USphereComponent* BoostSphere;
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BoostSphere")
		UStaticMeshComponent* BoostMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called when vehicle overlaps this
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
