// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsMenu.h"
#include "Menu.h"

AControlsMenu::AControlsMenu(const FObjectInitializer& rootMenu): mainMenu(&rootMenu)
{
}

void AControlsMenu::BeginPlay()
{
	Super::BeginPlay();
}

void AControlsMenu::Return()
{
}

void AControlsMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
