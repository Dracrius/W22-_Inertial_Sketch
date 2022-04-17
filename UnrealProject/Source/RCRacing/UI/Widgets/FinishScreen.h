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
#include "FinishScreen.generated.h"

//The Widget to show when the player has finished the Race
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

protected:
	UFinishScreen(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Finish();

	UFUNCTION(BlueprintCallable)
	virtual void QuitToMenu();

	UFUNCTION(BlueprintCallable)
	virtual void LoadPauseMenu();
};
