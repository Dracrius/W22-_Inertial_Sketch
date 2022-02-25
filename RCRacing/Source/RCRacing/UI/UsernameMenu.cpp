// Fill out your copyright notice in the Description page of Project Settings.


#include "UsernameMenu.h"
#include "Menu.h"

AUsernameMenu::AUsernameMenu(const FObjectInitializer& rootMenu): mainMenu(&rootMenu)
{
}

void AUsernameMenu::BeginPlay()
{
	Super::BeginPlay();
}

void AUsernameMenu::Return()
{
}

void AUsernameMenu::SetName(FText name)
{
}

void AUsernameMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
