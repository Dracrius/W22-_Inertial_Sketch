// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "GameFramework/GameStateBase.h"
#include "RCGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API ARCGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	FString playerName;

	bool isPaused;
	int menuSelection;

	class ACar* lastCar;
	float maxSpeed;
	std::vector<float> topScores;
	int numFlips;

	float musicVolume;
	float effectVolume;
	
};
