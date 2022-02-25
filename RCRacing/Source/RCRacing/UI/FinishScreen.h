// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/HUD.h"
#include "FinishScreen.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API AFinishScreen : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
		UFont* menuFont;

	FText playerName;
	int playerPos;
	std::vector<FText> racerNames;

	std::vector<float> finishTimes;
	float avgSpeed;
	int numFlips;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenus")
		class APauseMenu* pauseMenu;

protected:
	AFinishScreen();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void Finish();

	UFUNCTION()
	virtual void QuitToMenu();

	UFUNCTION()
	virtual void LoadPauseMenu();

public:
	virtual void Tick(float DeltaTime) override;
	
};
