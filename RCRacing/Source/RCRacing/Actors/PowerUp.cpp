// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Components/BoxComponent.h"
#include "RCRacing/Pawns/RCRacingPawn.h"
#include "RCRacing/Actors/BowlingBall_PowerUp.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PowerupBox"));
	PowerupBox->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PowerupBox->SetCollisionProfileName("BlockAllDynamic");
	PowerupBox->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	PowerupBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = PowerupBox;

	PowerupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerupMesh"));
	PowerupMesh->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PowerupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PowerupMesh->SetupAttachment(RootComponent);
}

void APowerUp::Use(FVector direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: USED!"));
	isPicked = false;
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();

	PowerupBox->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	PowerupBox->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
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

void APowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isPicked)
	{
		if (OtherActor != this)
		{
			ARCRacingPawn* playerPawn = Cast<ARCRacingPawn>(OtherActor);

			if (playerPawn)
			{
				int i = FMath::RandRange(1, 4);
				playerPawn->SetCurrentPowerUp(i);

				//if(this->IsA<ABowlingBall_PowerUp>())

				//playerPawn->SetCurrentPowerUp(this);
				Destroy();
			}
		}
	}
}

