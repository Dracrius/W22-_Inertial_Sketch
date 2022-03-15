// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingBall_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

class ARCRacingPawn;
// Sets default values
ABowlingBall_PowerUp::ABowlingBall_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionTemplate = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffectComponent"));
}

void ABowlingBall_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: USED!"));

	PowerupSphere->SetSimulatePhysics(true);
	PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PowerupSphere->SetNotifyRigidBodyCollision(true);
	PowerupSphere->GetBodyInstance()->AddForce(direction * -10000 * PowerupSphere->GetMass());
}

void ABowlingBall_PowerUp::Explode()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: BOOM!"));
	if (ExplosionTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());
	}
	Destroy();
}

// Called when the game starts or when spawned
void ABowlingBall_PowerUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABowlingBall_PowerUp::Tick(float DeltaTime)
{
	TimeUntilDespawn += DeltaTime;
	if (TimeUntilDespawn > MaxTimeUntilDespawn)
	{
		Destroy();
		TimeUntilDespawn = 0.0f;
	}
}

void ABowlingBall_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	if (isPicked)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				Explode();
				playerPawn->GotHit();
			}
				
		}
	}
}

void ABowlingBall_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}