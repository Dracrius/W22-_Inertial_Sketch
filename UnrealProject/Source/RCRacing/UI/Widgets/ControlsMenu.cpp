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


#include "ControlsMenu.h"
#include "../InGameUI.h"
#include "Engine/Font.h"

UControlsMenu::UControlsMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void UControlsMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

//Return to Pause Menu
void UControlsMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideControlsMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowPauseMenu();
}

//Return to Main Menu
void UControlsMenu::ReturnToMain()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideControlsMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

