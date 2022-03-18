// Fill out your copyright notice in the Description page of Project Settings.


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
}

////Called on space bar by the player
void AFreeze_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Freeze: USED!"));
}

// Called when the game starts or when spawned
void AFreeze_PowerUp::BeginPlay()
{
	Super::BeginPlay();
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
						playerPawn->Freezed(DeltaTime);
					}
				}
			}
			
			Destroy();
			m_Cooldown = 0.0f;
		}
	}
}