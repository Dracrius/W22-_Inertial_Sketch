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
}
