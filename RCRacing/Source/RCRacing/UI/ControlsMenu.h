// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "ControlsMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AControlsMenu : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	const FObjectInitializer* mainMenu;

protected:
	AControlsMenu(const FObjectInitializer& rootMenu);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Return();

public:
	virtual void Tick(float DeltaTime) override;
	
};
