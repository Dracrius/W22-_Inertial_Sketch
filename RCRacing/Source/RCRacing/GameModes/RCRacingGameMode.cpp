// Copyright Epic Games, Inc. All Rights Reserved.

#include "RCRacingGameMode.h"
#include "../Pawns/RCRacingPawn.h"
#include "../UI/RCRacingHud.h"

ARCRacingGameMode::ARCRacingGameMode()
{
	DefaultPawnClass = ARCRacingPawn::StaticClass();
	HUDClass = ARCRacingHud::StaticClass();
}
