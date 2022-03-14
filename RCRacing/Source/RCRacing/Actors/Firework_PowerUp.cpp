// Fill out your copyright notice in the Description page of Project Settings.


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

void AFirework_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: USED!"));

	isFired = true;

	PowerupSphere->SetSimulatePhysics(true);
	PowerupSphere->SetNotifyRigidBodyCollision(true);
	PowerupSphere->SetCollisionProfileName("Firework");
	PowerupSphere->GetBodyInstance()->AddForce(direction * 50000 * PowerupSphere->GetMass());
}

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
			PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PowerupSphere->SetCollisionProfileName("BlockAllDynamic");
			m_Cooldown = 0.0f;
		}
		
		if (TimeUntilDespawn > MaxTimeUntilDespawn)
		{
			Destroy();
			TimeUntilDespawn = 0.0f;
		}
	}

}

void AFirework_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

void AFirework_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
