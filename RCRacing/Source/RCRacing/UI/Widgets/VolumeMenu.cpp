// Fill out your copyright notice in the Description page of Project Settings.


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

}
