// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AMenu : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	FText playerName;

	class ACar* lastCar;
	float avgSpeed;
	std::vector<float> topScores;
	int numFlips;

	float musicVolume;
	float effectVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class AUsernameMenu* usernameMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class AVolumeMenu* volumeMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class AControlsMenu* controlsMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class ALocalRaceMenu* localRaceMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class ANetworkRaceMenu* networkRaceMenu;

protected:
	AMenu();

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
	virtual void LoadUsername();

	UFUNCTION()
	virtual void LoadVolume();

	UFUNCTION()
	virtual void LoadControls();

	UFUNCTION()
	virtual void LoadLocal();

	UFUNCTION()
	virtual void LoadNetwork();

	UFUNCTION()
	virtual void SetVolume(FText channel, float vol);

public:
	virtual void Tick(float DeltaTime) override;
	
};
