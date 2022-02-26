// Fill out your copyright notice in the Description page of Project Settings.


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
}

void UMainMenu::LoadVolumeMenu()
{
}

void UMainMenu::LoadControlsMenu()
{
}

void UMainMenu::LoadLocalMenu()
{
}

void UMainMenu::LoadNetworkMenu()
{
}

void UMainMenu::Quit()
{
}
