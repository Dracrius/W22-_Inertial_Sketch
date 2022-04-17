/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4

Changelog:
4/7
Completed Networking Adaptations
*/

#include "PowerUp.h"
#include "Components/BoxComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision sphere
	PowerupSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PowerupSphere"));
	//Sets collision to Block all
	PowerupSphere->SetCollisionProfileName("BlockAllDynamic");
	//Overlaps on Vehicles
	PowerupSphere->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	PowerupSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//sets PowerupSphere to be RootComponent
	RootComponent = PowerupSphere;

	//mesh
	PowerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerupMesh"));
	//Rotating the Mesh
	PowerupMesh->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	//No collision
	PowerupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Location at 0
	PowerupMesh->SetRelativeLocation(FVector(0));
	//attach the mesh to RootComponent 
	PowerupMesh->SetupAttachment(RootComponent);

	SetReplicates(true);
	SetReplicateMovement(true);
	bAlwaysRelevant = true;
}

//Starts when the player presses the use key space bar which calls the PowerUp’s Use function.
void APowerUp::Use(FVector direction, FVector SpawnPosition)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: USED!"));
	isPicked = false;
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	PowerupSphere->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	PowerupSphere->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
	PowerupMesh->SetIsReplicated(true);
}

// Called every frame

void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Create a dynamic and moving actor.
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

void APowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//set the player’s current power up to a random one.
	if (!isPicked && GetRemoteRole() != ROLE_Authority)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				RandomPowerUp = FMath::RandRange(1, 4);
				playerPawn->SetCurrentPowerUp(RandomPowerUp);
				this->SetActorHiddenInGame(true);
				this->SetActorEnableCollision(false);
				this->PowerupMesh = nullptr;
			}
		}
	}
}

