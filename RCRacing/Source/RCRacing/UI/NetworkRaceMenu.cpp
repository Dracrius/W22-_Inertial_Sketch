// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkRaceMenu.h"
#include "LocalRaceMenu.h"
#include "Menu.h"

ANetworkRaceMenu::ANetworkRaceMenu(const FObjectInitializer& rootMenu) : ALocalRaceMenu(rootMenu)
{
}

void ANetworkRaceMenu::BeginPlay()
{
	Super::BeginPlay();
}

void ANetworkRaceMenu::GetLobbies()
{
}

void ANetworkRaceMenu::SetLobby(FText lobby)
{
}

void ANetworkRaceMenu::GetRacers()
{
}

void ANetworkRaceMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
