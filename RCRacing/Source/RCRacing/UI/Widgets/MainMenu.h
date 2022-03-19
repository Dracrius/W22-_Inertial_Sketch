// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
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
