/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.1
Author : Alexander Achorn
Author : UE4

Changelog:
3/12
Switched to Widgets
3/16
Finished Basic Feature implimentation
3/19
Add Comments
*/


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
    //Needs Networking Implimentation
}

void UNetworkRaceMenu::SetLobby(FText lobby)
{
    //Needs Networking Implimentation
}

void UNetworkRaceMenu::GetRacers()
{
    //Needs Networking Implimentation
}