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
}

void UPauseMenu::LoadControls()
{
}

void UPauseMenu::ReturnToMenu()
{
}

void UPauseMenu::Continue()
{
}