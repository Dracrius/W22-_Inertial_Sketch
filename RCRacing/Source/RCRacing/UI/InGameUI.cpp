// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Widgets/MainMenu.h"
#include "Widgets/PauseMenu.h"
#include "Widgets/FinishScreen.h"
#include "Widgets/LocalRaceMenu.h"
#include "Widgets/NetworkRaceMenu.h"
#include "Widgets/UsernameMenu.h"
#include "Widgets/VolumeMenu.h"
#include "Widgets/ControlsMenu.h"
#include "Engine/Font.h"
#include "../GameStates/RCGameStateBase.h"
#include "Kismet/GameplayStatics.h"

AInGameUI::AInGameUI()
{
	menuFont = CreateDefaultSubobject<UFont>(TEXT("MenuFont"));

	playerName = FString("Player01");

	maxSpeed = 0.f;
	numFlips = 0;

	musicVolume = 100.f;
	effectVolume = 100.f;

	if (mainMenuClass)
	{
		mainMenu = CreateWidget<UMainMenu>(GetWorld(), mainMenuClass);

		if (mainMenuClass)
		{
			mainMenu->AddToViewport();
		}
	}

	if (pauseMenuClass)
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld(), pauseMenuClass);
	}

	if (finishScreenClass)
	{
		finishScreen = CreateWidget<UFinishScreen>(GetWorld(), finishScreenClass);
	}

	if (usernameMenuClass)
	{
		usernameMenu = CreateWidget<UUsernameMenu>(GetWorld(), usernameMenuClass);
	}

	if (volumeMenuClass)
	{
		volumeMenu = CreateWidget<UVolumeMenu>(GetWorld(), volumeMenuClass);
	}

	if (controlsMenuClass)
	{
		controlsMenu = CreateWidget<UControlsMenu>(GetWorld(), controlsMenuClass);
	}

	if (localRaceMenuClass)
	{
		localRaceMenu = CreateWidget<ULocalRaceMenu>(GetWorld(), localRaceMenuClass);
	}

	if (networkRaceMenuClass)
	{
		networkRaceMenu = CreateWidget<UNetworkRaceMenu>(GetWorld(), networkRaceMenuClass);
	}
}

void AInGameUI::DrawHUD()
{
}

void AInGameUI::BeginPlay()
{
	Super::BeginPlay();
	GetSave();
}

void AInGameUI::GetSave()
{
	bool save = false;

	if (save)
	{
		float mVol = 50.f; //Get from Save
		float eVol = 80.f; //Get from Save

		playerName = FString("Player01"); //Get from Save

		maxSpeed = 0.f; //Get from Save
		numFlips = 0; //Get from Save

		SetVolume(FString("Music"), mVol);
		SetVolume(FString("Effect"), eVol);
	}
	else
	{
		CreateFirstSave();
	}

	ARCGameStateBase* gState = Cast<ARCGameStateBase>(GetWorld()->GetGameState());

	gState->playerName = playerName;
	gState->musicVolume = musicVolume;
	gState->effectVolume = effectVolume;
}

void AInGameUI::CreateFirstSave()
{
	LoadUsernameMenu();

	float mVol = musicVolume; //Save to File
	float eVol = effectVolume; //Save to File

	FString name = playerName; //Save to File

	float maxSpd = maxSpeed; //Save to File
	float numFlps = numFlips; //Save to File
}

void AInGameUI::Save()
{

}

void AInGameUI::Quit()
{
	Save();
}

void AInGameUI::LoadMainMenu()
{

}

void AInGameUI::LoadPauseMenu()
{

}

void AInGameUI::LoadFinishMenu()
{

}

void AInGameUI::LoadUsernameMenu()
{

}

void AInGameUI::LoadVolumeMenu()
{

}

void AInGameUI::LoadControlsMenu()
{

}

void AInGameUI::LoadLocalMenu()
{

}

void AInGameUI::LoadNetworkMenu()
{

}

void AInGameUI::SetVolume(FString channel, float vol)
{
	ARCGameStateBase* gState = Cast<ARCGameStateBase>(GetWorld()->GetGameState());

	if (channel == FString("Music"))
	{
		musicVolume = vol;
		gState->musicVolume = musicVolume;
	}
	else if (channel == FString("Effect"))
	{
		effectVolume = vol;
		gState->effectVolume = effectVolume;
	}
}

void AInGameUI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}