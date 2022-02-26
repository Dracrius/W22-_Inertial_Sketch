// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AInGameUI : public AHUD
{
	GENERATED_BODY()
protected:
	class UMainMenu* mainMenu;
	class UPauseMenu* pauseMenu;
	class UFinishScreen* finishScreen;
	class UUsernameMenu* usernameMenu;
	class UVolumeMenu* volumeMenu;
	class UControlsMenu* controlsMenu;
	class ULocalRaceMenu* localRaceMenu;
	class UNetworkRaceMenu* networkRaceMenu;

public:
	UPROPERTY()
	UFont* menuFont;

	FString playerName;

	class ACar* lastCar;
	float maxSpeed;
	std::vector<float> topScores;
	int numFlips;

	float musicVolume;
	float effectVolume;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UMainMenu> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UPauseMenu> pauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UFinishScreen> finishScreenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UUsernameMenu> usernameMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UVolumeMenu> volumeMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UControlsMenu> controlsMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<ULocalRaceMenu> localRaceMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Menus")
	TSubclassOf<UNetworkRaceMenu> networkRaceMenuClass;

protected:
	AInGameUI();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void GetSave();

	UFUNCTION()
	virtual void CreateFirstSave();

	UFUNCTION()
	virtual void Save();

	UFUNCTION()
	virtual void Quit();

	UFUNCTION()
	virtual void LoadMainMenu();

	UFUNCTION()
	virtual void LoadPauseMenu();

	UFUNCTION()
	virtual void LoadFinishMenu();

	UFUNCTION()
	virtual void LoadUsernameMenu();

	UFUNCTION()
	virtual void LoadVolumeMenu();

	UFUNCTION()
	virtual void LoadControlsMenu();

	UFUNCTION()
	virtual void LoadLocalMenu();

	UFUNCTION()
	virtual void LoadNetworkMenu();

	UFUNCTION()
	virtual void SetVolume(FString channel, float vol);

public:
	virtual void Tick(float DeltaTime) override;
	
};
