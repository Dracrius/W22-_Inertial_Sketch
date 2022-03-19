// Fill out your copyright notice in the Description page of Project Settings.
//Version: 0.1
//Author : Antoine Plouffe




#include "Firework_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

class ARCRacingPawn;
// Sets default values
AFirework_PowerUp::AFirework_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionTemplate = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffectComponent"));
}

//Called on space bar by the player
void AFirework_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Firework: USED!"));

	isFired = true;

	PowerupSphere->SetSimulatePhysics(true);
	PowerupSphere->SetNotifyRigidBodyCollision(true);
	PowerupSphere->SetCollisionProfileName("Firework");
	PowerupSphere->GetBodyInstance()->AddForce(direction * 50000 * PowerupSphere->GetMass());
}

//Called when OnHit is triggered by a vehicle
void AFirework_PowerUp::Explode()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: BOOM!"));
	if (ExplosionTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());
	}
	Destroy();
}

// Called when the game starts or when spawned
void AFirework_PowerUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFirework_PowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFired)
	{
		m_Cooldown += DeltaTime;
		TimeUntilDespawn += DeltaTime;
		if (m_Cooldown > m_MaxCooldown)
		{
			//To ensure the power up won’t collide with the emitter (vehicle pawn), 
			PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PowerupSphere->SetCollisionProfileName("BlockAllDynamic");
			m_Cooldown = 0.0f;
		}
		
		if (TimeUntilDespawn > MaxTimeUntilDespawn)
		{
			//make sure the power up will be destroy if it doesn’t hit a vehicle within 5 seconds.
			Destroy();
			TimeUntilDespawn = 0.0f;
		}
	}

}

void AFirework_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
				Explode();
				playerPawn->GotHit();
			}

		}
	}
}