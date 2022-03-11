// Fill out your copyright notice in the Description page of Project Settings.


#include "Freeze_PowerUp.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

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
	//PowerupBox->GetBodyInstance()->AddForce(-direction * 100000 * PowerupBox->GetMass());
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
}

void AFreeze_PowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor != this)
	//{
	//	ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

	//	if (playerPawn)
	//		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Fuse, this, &AFreeze_PowerUp::Explode, 0.0f, false);
	//}
}

void AFreeze_PowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (isPicked)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				playerPawn->Freezed();
				Destroy();
			}
		}
	}
}
