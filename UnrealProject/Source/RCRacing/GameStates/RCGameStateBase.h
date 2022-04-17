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
