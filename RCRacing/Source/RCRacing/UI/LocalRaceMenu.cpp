// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalRaceMenu.h"
#include "Menu.h"

ALocalRaceMenu::ALocalRaceMenu(const FObjectInitializer& rootMenu) : mainMenu(&rootMenu)
{
}

void ALocalRaceMenu::BeginPlay()
{
	Super::BeginPlay();
}

void ALocalRaceMenu::StartRace()
{
}

void ALocalRaceMenu::Return()
{
}

void ALocalRaceMenu::NextCar()
{
}

void ALocalRaceMenu::PreviousCar()
{
}

void ALocalRaceMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
