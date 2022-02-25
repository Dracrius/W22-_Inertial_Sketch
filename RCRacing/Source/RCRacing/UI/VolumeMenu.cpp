// Fill out your copyright notice in the Description page of Project Settings.


#include "VolumeMenu.h"
#include "Menu.h"

AVolumeMenu::AVolumeMenu(const FObjectInitializer& rootMenu) : mainMenu(&rootMenu)
{
}

void AVolumeMenu::BeginPlay()
{
	Super::BeginPlay();
}

void AVolumeMenu::Return()
{
}

void AVolumeMenu::SetVolume(FText channel, float vol)
{
}

void AVolumeMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
