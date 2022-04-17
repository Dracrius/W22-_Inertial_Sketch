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
3/28
Started Networking Adaptations
4/16
Completed Networking Adaptations
*/


#include "NetworkRaceMenu.h"
#include "LocalRaceMenu.h"
#include "../InGameUI.h"
#include "Online_GameInstance.h"

UNetworkRaceMenu::UNetworkRaceMenu(const FObjectInitializer& rootMenu) : ULocalRaceMenu(rootMenu)
{
}

void UNetworkRaceMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UNetworkRaceMenu::HostLobby(FString LevelName)
{
    UOnline_GameInstance* GI = Cast<UOnline_GameInstance>(GetGameInstance());
    if (GI)
    {
        static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
        GI->Button_HostServer(LevelName);
    }
}

void UNetworkRaceMenu::JoinLobby()
{
    UOnline_GameInstance* GI = Cast<UOnline_GameInstance>(GetGameInstance());
    if (GI)
    {
        static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
        GI->Button_JoinServer();
    }
}

void UNetworkRaceMenu::GetLobbies()
{
    //Needs Networking Implimentation
}

void UNetworkRaceMenu::OpenMapSelect()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowNetworkMapMenu();
}

void UNetworkRaceMenu::GetRacers()
{
    //Needs Networking Implimentation
}

void UNetworkRaceMenu::Return()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void UNetworkRaceMenu::MapReturn()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMapMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowNetworkMenu();
}
