// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "UsernameMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AUsernameMenu : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	FText playerName;

	const FObjectInitializer* mainMenu;
protected:
	AUsernameMenu(const FObjectInitializer& rootMenu);

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Return();

	UFUNCTION()
	virtual void SetName(FText name);

public:
	virtual void Tick(float DeltaTime) override;
	
};
