// Fill out your copyright notice in the Description page of Project Settings.


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

void UPauseMenu::Quit()
{
}

void UPauseMenu::LoadVolume()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowVolumeMenu();
}

void UPauseMenu::LoadControls()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowControlsMenu();
}

void UPauseMenu::ReturnToMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HidePauseMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void UPauseMenu::Continue()
{
}