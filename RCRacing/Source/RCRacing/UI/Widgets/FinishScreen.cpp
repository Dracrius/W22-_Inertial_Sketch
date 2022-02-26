// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishScreen.h"
#include "../InGameUI.h"
#include "PauseMenu.h"
#include "Engine/Font.h"


UFinishScreen::UFinishScreen(const FObjectInitializer& rootMenu): UUserWidget(rootMenu)
{
	menuFont = CreateDefaultSubobject<UFont>(TEXT("MenuFont"));
}

void UFinishScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UFinishScreen::Finish()
{
}

void UFinishScreen::QuitToMenu()
{
}

void UFinishScreen::LoadPauseMenu()
{
}

