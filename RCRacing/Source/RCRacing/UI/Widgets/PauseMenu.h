// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
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

	float musicVolume;
	float effectVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class UVolumeMenu* volumeMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
	class UControlsMenu* controlsMenu;

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
