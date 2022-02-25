// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "LocalRaceMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API ALocalRaceMenu : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	FText playerName;

	class ACar* currentCar;
	std::vector<ACar*> cars;
	float avgSpeed;
	std::vector<float> topScores;
	int numFlips;

	float musicVolume;
	float effectVolume;

	const FObjectInitializer* mainMenu;

protected:
	ALocalRaceMenu(const FObjectInitializer& rootMenu);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void StartRace();

	UFUNCTION()
	virtual void Return();

	UFUNCTION()
	virtual void NextCar();

	UFUNCTION()
	virtual void PreviousCar();

public:
	virtual void Tick(float DeltaTime) override;
	
};
