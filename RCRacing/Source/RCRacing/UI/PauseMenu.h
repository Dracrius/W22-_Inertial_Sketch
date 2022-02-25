// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API APauseMenu : public AHUD
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
	class AVolumeMenu* volumeMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class AControlsMenu* controlsMenu;

protected:
	APauseMenu();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Quit();

	UFUNCTION()
	virtual void LoadVolume();

	UFUNCTION()
	virtual void LoadControls();

	UFUNCTION()
	virtual void ReturnToMenu();

	UFUNCTION()
	virtual void Continue();

public:
	virtual void Tick(float DeltaTime) override;
	
};
