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


#include "PauseMenu.h"
#include "../InGameUI.h"
#include "ControlsMenu.h"
#include "VolumeMenu.h"

UPauseMenu::UPauseMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

//Quit the Game
void UPauseMenu::Quit()
{
    //Handled in Blueprint will likely Remove if there is no future use
}

//Show Volume Menu
void UPauseMenu::LoadVolume()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowVolumeMenu();
}

//Show Controls Menu
void UPauseMenu::LoadControls()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowControlsMenu();
}

//Return to Main Menu
void UPauseMenu::ReturnToMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

//Return to Game
void UPauseMenu::Continue()
{
    //Simply hides the menu and returns Control to the Car
    static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
}