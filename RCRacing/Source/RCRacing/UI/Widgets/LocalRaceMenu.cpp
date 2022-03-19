// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalRaceMenu.h"
#include "../InGameUI.h"

ULocalRaceMenu::ULocalRaceMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
}

void ULocalRaceMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULocalRaceMenu::StartRace()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideLocalMenu();
}

void ULocalRaceMenu::Return()
{
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->HideLocalMenu();
	static_cast<AInGameUI*>(GetOwningPlayer()->GetHUD())->ShowMainMenu();
}

void ULocalRaceMenu::NextCar()
{
}

void ULocalRaceMenu::PreviousCar()
{
}
