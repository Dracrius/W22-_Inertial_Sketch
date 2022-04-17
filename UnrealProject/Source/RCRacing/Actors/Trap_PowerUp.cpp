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

#include "Trap_PowerUp.h"

#include "Components/BoxComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"
class ARCRacingPawn;
// Sets default values
ATrap_PowerUp::ATrap_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ATrap_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	PowerupMesh->SetIsReplicated(true);
}

// Called every frame
void ATrap_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrap_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//create a wow moment when the player overlaps a trap by moving upwards and rotating their vehicle mesh
	if (isPicked)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				playerPawn->OnRepTrapped(Cast<AWheeledVehicle>(OtherActor));

				this->SetActorHiddenInGame(true);
				this->SetActorEnableCollision(false);
				this->PowerupMesh = nullptr;
			}
		}
	}
}

//Called on space bar by the player
void ATrap_PowerUp::Use(FVector direction, FVector SpawnPosition)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trap: USED!"));
	SetActorLocation(SpawnPosition);
}