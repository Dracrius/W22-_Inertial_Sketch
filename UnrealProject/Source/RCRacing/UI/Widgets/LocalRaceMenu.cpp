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
*/


#include "LocalRaceMenu.h"
#include "../InGameUI.h"

ULocalRaceMenu::ULocalRaceMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void ULocalRaceMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

//Start a Local Race
void ULocalRaceMenu::StartRace()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideLocalMenu();
}

//Return to Main Menu
void ULocalRaceMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideLocalMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

//Move to Next Car - Not Implemented Yet
void ULocalRaceMenu::NextCar()
{
    //Needs Car Bodies to be Implimented
}

//Move to Previous Car - Not Implemented Yet
void ULocalRaceMenu::PreviousCar()
{
    //Needs Car Bodies to be Implimented
}
