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

public:
	UFUNCTION(BlueprintCallable)
	virtual void GetSave();

	UFUNCTION(BlueprintCallable)
	virtual void CreateFirstSave();

	UFUNCTION(BlueprintCallable)
	virtual void Save();

	UFUNCTION(BlueprintCallable)
	virtual void Quit();

	UFUNCTION(BlueprintCallable)
	virtual void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideMainMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HidePauseMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowFinishMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideFinishMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowUsernameMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideUsernameMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowVolumeMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideVolumeMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowControlsMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideControlsMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowLocalMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideLocalMenu();

	UFUNCTION(BlueprintCallable)
	virtual void ShowNetworkMenu();

	UFUNCTION(BlueprintCallable)
	virtual void HideNetworkMenu();

	UFUNCTION(BlueprintCallable)
	virtual void SetVolume(FString channel, float vol);

	virtual void Tick(float DeltaTime) override;
	
};
