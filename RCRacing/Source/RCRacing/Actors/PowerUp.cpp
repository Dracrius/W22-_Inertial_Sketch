// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "Components/BoxComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("PowerupBox"));
	PowerupBox->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PowerupBox->SetCollisionProfileName("BlockAllDynamic");
	PowerupBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PowerupBox->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	PowerupBox->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnOverlapBegin);
	RootComponent = PowerupBox;

	PowerupMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("PowerupMesh"));
	PowerupMesh->SetRelativeRotation(FRotator(-45.0f, 0, 0));
	PowerupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PowerupMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUp::RandomizePowerup()
{
	int i = FMath::RandRange(1, 4);

	if (i == 1)
	{
		TrapPowerUp();
	}
	else if (i == 2)
	{
		FreezePowerUp();
	}
	else if (i == 3)
	{
		BowlingBallPowerUp();
	}
	else if (i == 4)
	{
		FireworkPowerUp();
	}
}

void APowerUp::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                     FVector NormalImpulse, const FHitResult& Hit)
{
}

void APowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor,	UPrimitiveComponent* OtherComp,	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APowerUp::FreezePowerUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: Freeze!"));
}

void APowerUp::TrapPowerUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: Trap!"));
}

void APowerUp::BowlingBallPowerUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: Bowling ball!"));
}

void APowerUp::FireworkPowerUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Powerup: Firework!"));
}

