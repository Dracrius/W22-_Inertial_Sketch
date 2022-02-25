// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "LocalRaceMenu.h"
#include "NetworkRaceMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API ANetworkRaceMenu : public ALocalRaceMenu
{
	GENERATED_BODY()
public:
	FText currentLobby;

	std::vector<FText> lobbyNames;
	std::vector<FText> NetworkRacers;

protected:
	ANetworkRaceMenu(const FObjectInitializer& rootMenu);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void GetLobbies();

	UFUNCTION()
	virtual void SetLobby(FText lobby);

	UFUNCTION()
	virtual void GetRacers();

public:
	virtual void Tick(float DeltaTime) override;
	
};
