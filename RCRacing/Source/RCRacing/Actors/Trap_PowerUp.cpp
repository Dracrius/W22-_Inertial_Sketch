// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap_PowerUp.h"

#include "Components/BoxComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"
class ARCRacingPawn;
// Sets default values
ATrap_PowerUp::ATrap_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrap_PowerUp::BeginPlay()
{
	Super::BeginPlay();
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
				playerPawn->Trapped();
				Destroy();
			}
		}
	}
}

//Called on space bar by the player
void ATrap_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trap: USED!"));
}