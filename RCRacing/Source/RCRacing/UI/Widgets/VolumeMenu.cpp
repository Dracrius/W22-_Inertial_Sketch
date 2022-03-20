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


#include "VolumeMenu.h"
#include "../InGameUI.h"

UVolumeMenu::UVolumeMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void UVolumeMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UVolumeMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideVolumeMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowPauseMenu();
}

void UVolumeMenu::ReturnToMain()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideVolumeMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void UVolumeMenu::SetVolume(FText channel, float vol)
{
    //Need to learn how to Set Game Volumes Requires some implimentation of a custom sound engine from what I have seen.
}
