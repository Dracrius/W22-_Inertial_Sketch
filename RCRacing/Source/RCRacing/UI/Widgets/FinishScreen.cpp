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


#include "FinishScreen.h"
#include "../InGameUI.h"
#include "PauseMenu.h"
#include "Engine/Font.h"


UFinishScreen::UFinishScreen(const FObjectInitializer& rootMenu): UUserWidget(rootMenu)
{
}

void UFinishScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFinishScreen::Finish()
{
    //Will Hide menu and set a panning Camera once we have laps and a Finish
}

void UFinishScreen::QuitToMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideFinishMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void UFinishScreen::LoadPauseMenu()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideFinishMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowPauseMenu();
}

