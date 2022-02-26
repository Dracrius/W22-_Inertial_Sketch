// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlsMenu.h"
#include "../InGameUI.h"
#include "Engine/Font.h"

UControlsMenu::UControlsMenu(const FObjectInitializer& rootMenu) : UUserWidget(rootMenu)
{
	menuFont = CreateDefaultSubobject<UFont>(TEXT("MenuFont"));
}

void UControlsMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UControlsMenu::Return()
{
}

