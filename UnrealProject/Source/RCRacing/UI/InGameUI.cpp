/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4

Changelog:
3/10
First Attempt
3/12
Rewrite Everything had the wrong idea
3/16
Finished Major Feature implimentation
3/19
Add Comments
4/16
Completed Networking Adaptations
*/


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
    //Lets Set Things Up!
	menuFont = CreateDefaultSubobject<UFont>(TEXT("MenuFont"));

	playerName = FString("Player01");

	maxSpeed = 0.f;
	numFlips = 0;

	musicVolume = 100.f;
	effectVolume = 100.f;

    //Fill the Widget Pointers
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

    if (networkMapMenuClass)
    {
        networkMapMenu = CreateWidget<UNetworkRaceMenu>(GetWorld(), networkMapMenuClass);
    }
}

void AInGameUI::DrawHUD()
{
}

void AInGameUI::BeginPlay()
{
	Super::BeginPlay();

    //Commented Out until Save Files are added so you don't end up in a "What's your Name?" Loop
	//GetSave();
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

        //Set Volumes Base on Saved Values
		SetVolume(FString("Music"), mVol);
		SetVolume(FString("Effect"), eVol);
	}
	else
	{
        //If there is no Save make one
		CreateFirstSave();
	}


    //Get the Game State and apply the saved settings
	ARCGameStateBase* gState = Cast<ARCGameStateBase>(GetWorld()->GetGameState());

	gState->playerName = playerName;
	gState->musicVolume = musicVolume;
	gState->effectVolume = effectVolume;
}

void AInGameUI::CreateFirstSave()
{
    //There was no save file so we ask the user for their name so we can make one
	HideMainMenu();
	ShowUsernameMenu();

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

void AInGameUI::ShowMainMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	if (mainMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		mainMenu = CreateWidget<UMainMenu>(PC, mainMenuClass);
	}

	mainMenu->AddToViewport();
}

void AInGameUI::HideMainMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (mainMenu)
	{
		mainMenu->RemoveFromViewport();
		mainMenu = nullptr;
	}
}

void AInGameUI::ShowPauseMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (pauseMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		pauseMenu = CreateWidget<UPauseMenu>(PC, pauseMenuClass);
	}

	pauseMenu->AddToViewport();
}

void AInGameUI::HidePauseMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (pauseMenu)
	{
		pauseMenu->RemoveFromViewport();
		pauseMenu = nullptr;
	}
}

void AInGameUI::ShowFinishMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (finishScreenClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		finishScreen = CreateWidget<UFinishScreen>(PC, finishScreenClass);
	}

	finishScreen->AddToViewport();
}

void AInGameUI::HideFinishMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (finishScreen)
	{
		finishScreen->RemoveFromViewport();
		finishScreen = nullptr;
	}
}

void AInGameUI::ShowUsernameMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (usernameMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		usernameMenu = CreateWidget<UUsernameMenu>(PC, usernameMenuClass);
	}

	usernameMenu->AddToViewport();
}

void AInGameUI::HideUsernameMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (usernameMenu)
	{
		usernameMenu->RemoveFromViewport();
		usernameMenu = nullptr;
	}
}

void AInGameUI::ShowVolumeMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (volumeMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		volumeMenu = CreateWidget<UVolumeMenu>(PC, volumeMenuClass);
	}

	volumeMenu->AddToViewport();
}

void AInGameUI::HideVolumeMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (volumeMenu)
	{
		volumeMenu->RemoveFromViewport();
		volumeMenu = nullptr;
	}
}

void AInGameUI::ShowControlsMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (controlsMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		controlsMenu = CreateWidget<UControlsMenu>(PC, controlsMenuClass);
	}

	controlsMenu->AddToViewport();
}

void AInGameUI::HideControlsMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (controlsMenu)
	{
		controlsMenu->RemoveFromViewport();
		controlsMenu = nullptr;
	}
}

void AInGameUI::ShowLocalMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (localRaceMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		localRaceMenu = CreateWidget<ULocalRaceMenu>(PC, localRaceMenuClass);
	}

	localRaceMenu->AddToViewport();
}

void AInGameUI::HideLocalMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (localRaceMenu)
	{
		localRaceMenu->RemoveFromViewport();
		localRaceMenu = nullptr;
	}
}

void AInGameUI::ShowNetworkMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	if (networkRaceMenuClass)
	{
		APlayerController* PC = Cast<APlayerController>(GetOwner());
		networkRaceMenu = CreateWidget<UNetworkRaceMenu>(PC, networkRaceMenuClass);
	}

	networkRaceMenu->AddToViewport();
}

void AInGameUI::HideNetworkMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

	if (networkRaceMenu)
	{
		networkRaceMenu->RemoveFromViewport();
		networkRaceMenu = nullptr;
	}
}

void AInGameUI::ShowNetworkMapMenu()
{
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

    if (networkRaceMenuClass)
    {
        APlayerController* PC = Cast<APlayerController>(GetOwner());
        networkMapMenu = CreateWidget<UNetworkRaceMenu>(PC, networkMapMenuClass);
    }

    networkMapMenu->AddToViewport();
}

void AInGameUI::HideNetworkMapMenu()
{
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameOnly());
    UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;

    if (networkRaceMenu)
    {
        networkMapMenu->RemoveFromViewport();
        networkMapMenu = nullptr;
    }
}

void AInGameUI::SetVolume(FString channel, float vol)
{
    //Get the game state so that we can set our volumes to what was set
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