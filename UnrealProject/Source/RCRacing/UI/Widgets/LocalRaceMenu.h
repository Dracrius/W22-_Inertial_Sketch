/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "LocalRaceMenu.generated.h"

//The Menu used for Single Player Races
UCLASS()
class RCRACING_API ULocalRaceMenu : public UUserWidget
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

protected:
	ULocalRaceMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void StartRace();

	UFUNCTION(BlueprintCallable)
	virtual void Return();

	UFUNCTION(BlueprintCallable)
	virtual void NextCar();

	UFUNCTION(BlueprintCallable)
	virtual void PreviousCar();

public:
	
};
