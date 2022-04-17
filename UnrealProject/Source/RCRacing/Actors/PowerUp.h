/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4
*/
#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
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

protected:

	//Collision sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUpSphere")
		USphereComponent* PowerupSphere;
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PowerUpSphere")
		UStaticMeshComponent* PowerupMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMeshToNull() { PowerupMesh = nullptr; }

	//OnHit and OnOverlap Virtual functions
	//UFUNCTION(Server, Reliable)
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			FVector NormalImpulse, const FHitResult& Hit);
	//UFUNCTION(Server, Reliable)
	UFUNCTION()
		virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Called on space bar by the player
	virtual void Use(FVector direction, FVector SpawnPosition);

	//Setters
	void SetActive(bool isActive) { m_IsActive = isActive; }
	void SetPicked(bool picked) { isPicked = picked; }
	void SetUsed(bool used) { isUsed = used; }

	//Getters
	bool GetActive() { return m_IsActive; }

	// Member variables
	bool bImGoingUp = true;
	bool m_IsActive;

	// Members accessible from UE
	//switches
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		bool isPicked = false;
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		bool isUsed = false;

	//Cooldowns
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		float m_Cooldown;
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		float m_MaxCooldown = 2.0f;
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		float TimeUntilDespawn;
	UPROPERTY(EditAnywhere, Category = "PowerUpStatus")
		float MaxTimeUntilDespawn = 5.0f;

	//Random 
	UPROPERTY(EditAnywhere, Category = "PowerUp")
		int RandomPowerUp;
};
