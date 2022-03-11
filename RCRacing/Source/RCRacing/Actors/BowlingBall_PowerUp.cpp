// Fill out your copyright notice in the Description page of Project Settings.


#include "BowlingBall_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

class ARCRacingPawn;
// Sets default values
ABowlingBall_PowerUp::ABowlingBall_PowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PowerupSphere"));
	PowerupSphere->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = PowerupSphere;
}

void ABowlingBall_PowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bowling Ball: USED!"));

	PowerupSphere->SetSimulatePhysics(true);
	PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PowerupSphere->SetNotifyRigidBodyCollision(true);
	PowerupSphere->GetBodyInstance()->AddForce(-direction * 10000 * PowerupBox->GetMass());
}

void ABowlingBall_PowerUp::Explode()
{
}

// Called when the game starts or when spawned
void ABowlingBall_PowerUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABowlingBall_PowerUp::Tick(float DeltaTime)
{

}

void ABowlingBall_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

		if (playerPawn)
			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Fuse, this, &ABowlingBall_PowerUp::Explode, 0.0f, false);
	}
}

void ABowlingBall_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	//if (OtherActor != this)
	//{
	//	ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

	//	if (playerPawn)
	//	{
	//		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Fuse, this, &ABowlingBall_PowerUp::Explode, 0.0f, false);
	//	}
	//}
}
