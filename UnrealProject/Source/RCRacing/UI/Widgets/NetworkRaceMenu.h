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
#include "LocalRaceMenu.h"
#include "NetworkRaceMenu.generated.h"

//The Menu used to select a Network Server/ Race
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
    virtual void HostLobby(FString LevelName);

    UFUNCTION(BlueprintCallable)
    virtual void JoinLobby();

	UFUNCTION(BlueprintCallable)
	virtual void GetLobbies();

	UFUNCTION(BlueprintCallable)
	virtual void OpenMapSelect();

	UFUNCTION(BlueprintCallable)
	virtual void GetRacers();

    virtual void Return() override;

    UFUNCTION(BlueprintCallable)
    virtual void MapReturn();

};
