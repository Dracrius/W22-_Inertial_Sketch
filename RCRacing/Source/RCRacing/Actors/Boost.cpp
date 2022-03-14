// Fill out your copyright notice in the Description page of Project Settings.


#include "Boost.h"

#include "Components/SphereComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

// Sets default values
ABoost::ABoost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoostSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PowerupSphere"));
	BoostSphere->SetCollisionProfileName("BlockAllDynamic");
	BoostSphere->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	BoostSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = BoostSphere;

	BoostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerupMesh"));
	BoostMesh->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	BoostMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoostMesh->SetRelativeLocation(FVector(0));
	BoostMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoost::BeginPlay()
{
	Super::BeginPlay();
	BoostSphere->OnComponentBeginOverlap.AddDynamic(this, &ABoost::OnOverlapBegin);
}

// Called every frame
void ABoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoost::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

		if (playerPawn)
		{
			playerPawn->Boost();
		}
	}
}

