// Fill out your copyright notice in the Description page of Project Settings.


#include "Firework_PowerUp.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "PhysicsEngine/RadialForceComponent.h"

class ARCRacingPawn;
// Sets default values
AFirework_PowerUp::AFirework_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//VFX
	ExplosionTemplate = CreateDefaultSubobject<UParticleSystem>(TEXT("ExplosionEffectComponent"));

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->ForceStrength = 1000.0f;
	RadialForceComponent->ImpulseStrength = 1000.0f;
	RadialForceComponent->Radius = 250.0f;
	RadialForceComponent->SetupAttachment(RootComponent);
}


void AFirework_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Firework: USED!"));

	PowerupBox->SetSimulatePhysics(true);
	PowerupBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PowerupBox->SetNotifyRigidBodyCollision(true);
	PowerupBox->GetBodyInstance()->AddForce(direction * 100000 * PowerupBox->GetMass());
}

void AFirework_PowerUp::Explode()
{
	RadialForceComponent->FireImpulse();
	UGameplayStatics::ApplyRadialDamage(this, 100, this->GetActorLocation(), 250.0f, UDamageType::StaticClass(),
		TArray<AActor*>(), this);
	if (ExplosionTemplate)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionTemplate, GetActorLocation());
	}
	FTimerHandle DestroyHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &AFirework_PowerUp::DestroyBomb, 1.f, false);
}

void AFirework_PowerUp::DestroyBomb()
{
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
	//RootComponent->SetRelativeLocation(FVector(RootComponent->GetForwardVector() * DeltaTime));
}

void AFirework_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor != this)
	//{
	//	Explode();
	//}
}

void AFirework_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}