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

void AFreeze_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Freeze: USED!"));
}

void AFreeze_PowerUp::Explode()
{
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

	if (isPicked && isUsed)
	{
		m_Cooldown += DeltaTime;
		if (m_Cooldown > m_MaxCooldown)
		{
			const FVector Start = GetActorLocation();
			const FVector End = GetActorLocation();

			TArray<AActor*> ActorsToIgnore;

			//ActorsToIgnore.Add(GetOwner());
			TArray<FHitResult> HitArray;

			const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, TraceRadius, ETraceTypeQuery::TraceTypeQuery1,
				false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitArray, true, FLinearColor::Green, FLinearColor::Blue, 0.0f);

			if (Hit)
			{
				m_Cooldown += DeltaTime;
				if (m_Cooldown > m_MaxCooldown)
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
			}
			
			Destroy();
			m_Cooldown = 0.0f;
		}
	}
}

void AFreeze_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AFreeze_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
