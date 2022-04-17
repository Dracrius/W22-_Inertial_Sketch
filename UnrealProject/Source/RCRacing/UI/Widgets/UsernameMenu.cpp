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


#include "UsernameMenu.h"
#include "../InGameUI.h"

UUsernameMenu::UUsernameMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void UUsernameMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

//Return to Main Menu
void UUsernameMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideUsernameMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

//Set the Players Username - Not Implemented
void UUsernameMenu::SetName(FText name)
{
    //Need to add Save Files to Store this.
}