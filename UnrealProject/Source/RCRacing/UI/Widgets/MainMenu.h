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
#include "MainMenu.generated.h"

//The Main Menu entered when starting the game or Returning to Menu
UCLASS()
class RCRACING_API UMainMenu : public UUserWidget
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

protected:
	UMainMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		virtual void LoadUsernameMenu();

	UFUNCTION(BlueprintCallable)
		virtual void LoadVolumeMenu();

	UFUNCTION(BlueprintCallable)
		virtual void LoadControlsMenu();

	UFUNCTION(BlueprintCallable)
		virtual void LoadLocalMenu();

	UFUNCTION(BlueprintCallable)
		virtual void LoadNetworkMenu();

	UFUNCTION(BlueprintCallable)
		virtual void Quit();

public:
	
};
