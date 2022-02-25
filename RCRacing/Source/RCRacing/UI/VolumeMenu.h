// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "VolumeMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AVolumeMenu : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	float musicVolume;
	float effectVolume;

	const FObjectInitializer* mainMenu;

protected:
	AVolumeMenu(const FObjectInitializer& rootMenu);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Return();

	UFUNCTION()
	virtual void SetVolume(FText channel, float vol);

public:
	virtual void Tick(float DeltaTime) override;
	
};
