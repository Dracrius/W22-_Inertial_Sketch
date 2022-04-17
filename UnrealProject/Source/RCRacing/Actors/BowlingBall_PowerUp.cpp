/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4

Changelog:
4/7
Completed Networking Adaptations
*/

#include "BowlingBall_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "RCRacing/Pawns/RCRacingPawn.h"
#include "DrawDebugHelpers.h"

class ARCRacingPawn;
// Sets default values
ABowlingBall_PowerUp::ABowlingBall_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionTemplate = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffectComponent"));

	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
}

//Called on space bar by the player
void ABowlingBall_PowerUp::Use(FVector direction, FVector SpawnPosition)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: USED!"));

	isFired = true;
	
	PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PowerupSphere->SetNotifyRigidBodyCollision(true);
	SetActorLocation(SpawnPosition);

	PowerupSphere->GetBodyInstance()->AddForce(-direction * 100000 * PowerupSphere->GetMass());

}

//Called when OnHit is triggered by a vehicle
void ABowlingBall_PowerUp::NetMulticastExplode_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: BOOM!"));

	if (ExplosionTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());
	}
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PowerupMesh = nullptr;
}

// Called when the game starts or when spawned
void ABowlingBall_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	PowerupMesh->SetIsReplicated(true);
	SetActorEnableCollision(false);
}

// Called every frame
void ABowlingBall_PowerUp::Tick(float DeltaTime)
{
	if (isFired)
	{
		TimeUntilDespawn += DeltaTime;
		if (TimeUntilDespawn > MaxTimeUntilDespawn)
		{
			//make sure the power up will be destroy if it doesn’t hit a vehicle within 5 seconds.
			this->SetActorHiddenInGame(true);
			this->SetActorEnableCollision(false);
			this->PowerupMesh = nullptr;
			TimeUntilDespawn = 0.0f;
		}
	}
}

void ABowlingBall_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	//starts when the power up collision sphere hits a vehicle
	//Calls Explode function
	if (isPicked)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				NetMulticastExplode();
				playerPawn->OnRepGotHit();
			}

		}
	}
}