// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameMenu.h"
#include "../InGameUI.h"

UUsernameMenu::UUsernameMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{

}

void UUsernameMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUsernameMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideUsernameMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void UUsernameMenu::SetName(FText name)
{

}