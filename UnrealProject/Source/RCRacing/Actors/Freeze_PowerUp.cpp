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

#include "Freeze_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"
#include "Kismet/KismetSystemLibrary.h"

class ARCRacingPawn;
// Sets default values
AFreeze_PowerUp::AFreeze_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
}

////Called on space bar by the player
void AFreeze_PowerUp::Use(FVector direction, FVector SpawnPosition)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Freeze: USED!"));
	SetActorLocation(SpawnPosition);

}

// Called when the game starts or when spawned
void AFreeze_PowerUp::BeginPlay()
{
	Super::BeginPlay();
	PowerupMesh->SetIsReplicated(true);
}

// Called every frame
void AFreeze_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//detect the actors and pawns in a radius around the power up by using SphereTraceMulti
	if (isPicked && isUsed)
	{
		m_Cooldown += DeltaTime;
		if (m_Cooldown > m_MaxCooldown)
		{
			const FVector Start = GetActorLocation();
			const FVector End = GetActorLocation();

			//AActor*: used as an ignore list for the SphereTraceMulti.
			//FHitResult * : used to get the hit result from SphereTraceMulti.
			TArray<AActor*> ActorsToIgnore;
			TArray<FHitResult> HitArray;

			const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, TraceRadius, ETraceTypeQuery::TraceTypeQuery1,
				false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitArray, true, FLinearColor::Green, FLinearColor::Blue, 0.0f);

			//then apply the freeze effect when it hits the right target.
			if (Hit)
			{
				for (const FHitResult HitResult : HitArray)
				{
					ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(HitResult.GetActor());
					if (playerPawn)
					{
						playerPawn->OnRepFreezed(DeltaTime);
					}
				}
			}
			
			this->SetActorHiddenInGame(true);
			this->SetActorEnableCollision(false);
			this->PowerupMesh = nullptr;
			m_Cooldown = 0.0f;
		}
	}
}