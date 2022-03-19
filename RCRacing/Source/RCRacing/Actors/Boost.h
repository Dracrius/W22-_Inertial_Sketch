// Fill out your copyright notice in the Description page of Project Settings.
//Version: 0.1
//Author : Antoine Plouffe

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
