// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "FinishScreen.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API UFinishScreen : public UUserWidget
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SubMenu")
	class UPauseMenu* pauseMenu;

protected:
	UFinishScreen(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void Finish();

	UFUNCTION()
	virtual void QuitToMenu();

	UFUNCTION()
	virtual void LoadPauseMenu();

public:
	
};
