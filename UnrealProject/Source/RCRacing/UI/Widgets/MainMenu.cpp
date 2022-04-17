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
Finished Major Feature implimentation
3/19
Add Comments
*/


#include "MainMenu.h"
#include "../InGameUI.h"
#include "ControlsMenu.h"
#include "VolumeMenu.h"

UMainMenu::UMainMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainMenu::LoadUsernameMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideMainMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowUsernameMenu();
}

void UMainMenu::LoadVolumeMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideMainMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowVolumeMenu();
}

void UMainMenu::LoadControlsMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideMainMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowControlsMenu();
}

void UMainMenu::LoadLocalMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideMainMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowLocalMenu();
}

void UMainMenu::LoadNetworkMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideMainMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowNetworkMenu();
}

void UMainMenu::Quit()
{
    //Handled in Blueprint will Likely Remove if there is no future use
}
