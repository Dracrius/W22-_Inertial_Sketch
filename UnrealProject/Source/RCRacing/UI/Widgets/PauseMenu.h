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
#include "PauseMenu.generated.h"

//The Pause Menu for while in Game
UCLASS()
class RCRACING_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UFont* menuFont;

	FText playerName;

	float avgSpeed;
	int numFlips;

protected:
	UPauseMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Quit();

	UFUNCTION(BlueprintCallable)
	virtual void LoadVolume();

	UFUNCTION(BlueprintCallable)
	virtual void LoadControls();

	UFUNCTION(BlueprintCallable)
	virtual void ReturnToMenu();

	UFUNCTION(BlueprintCallable)
	virtual void Continue();
};
