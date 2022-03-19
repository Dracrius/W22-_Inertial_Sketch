// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "LocalRaceMenu.h"
#include "NetworkRaceMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API UNetworkRaceMenu : public ULocalRaceMenu
{
	GENERATED_BODY()
public:
	FText currentLobby;

	std::vector<FText> lobbyNames;
	std::vector<FText> NetworkRacers;

protected:
	UNetworkRaceMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void GetLobbies();

	UFUNCTION(BlueprintCallable)
	virtual void SetLobby(FText lobby);

	UFUNCTION(BlueprintCallable)
	virtual void GetRacers();
};
