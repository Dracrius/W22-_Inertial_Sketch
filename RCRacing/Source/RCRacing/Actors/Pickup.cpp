// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "PowerUp.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	PickupBox->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PickupBox->SetCollisionProfileName("BlockAllDynamic");
	PickupBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupBox->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	PickupBox->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
	RootComponent = PickupBox;

	PickupMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	if (NewLocation.Z > 60.0f) {
		bImGoingUp = false;
	}
	else if (NewLocation.Z < 30.0f) {
		bImGoingUp = true;
	}
	float factor = (bImGoingUp ? 10.f : -10.f);
	NewLocation.Z += factor * DeltaTime;
	SetActorLocation(NewLocation);

}

void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		Destroy();

		if (PowerupClass)
		{
			APowerUp* power = Cast<APowerUp>(this->GetClass());
			power->RandomizePowerup();
		}
	}
}

