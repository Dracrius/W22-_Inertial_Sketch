// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkRaceMenu.h"
#include "LocalRaceMenu.h"
#include "../InGameUI.h"

UNetworkRaceMenu::UNetworkRaceMenu(const FObjectInitializer& rootMenu) : ULocalRaceMenu(rootMenu)
{
}

void UNetworkRaceMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNetworkRaceMenu::GetLobbies()
{
}

void UNetworkRaceMenu::SetLobby(FText lobby)
{
}

void UNetworkRaceMenu::GetRacers()
{
}