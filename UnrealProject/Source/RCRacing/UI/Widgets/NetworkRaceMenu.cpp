/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
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

//Start Hosting a Network Lobby
void UNetworkRaceMenu::HostLobby(FString LevelName)
{
    UOnline_GameInstance* GI = Cast<UOnline_GameInstance>(GetGameInstance());
    if (GI)
    {
        static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
        GI->Button_HostServer(LevelName);
    }
}

//Join an Active Network Lobby
void UNetworkRaceMenu::JoinLobby()
{
    UOnline_GameInstance* GI = Cast<UOnline_GameInstance>(GetGameInstance());
    if (GI)
    {
        static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
        GI->Button_JoinServer();
    }
}

//Get List of Lobbies - Not Implemented Yet
void UNetworkRaceMenu::GetLobbies()
{
    //Needs Networking Implimentation
}

//Open the Map Select Menu after Choosing to Host
void UNetworkRaceMenu::OpenMapSelect()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowNetworkMapMenu();
}

//Get List of Racers - Not Implemented Yet
void UNetworkRaceMenu::GetRacers()
{
    //Needs Networking Implimentation
}

//Return to Networking Menu
void UNetworkRaceMenu::Return()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

//Return to Main Menu
void UNetworkRaceMenu::MapReturn()
{
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideNetworkMapMenu();
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowNetworkMenu();
}
