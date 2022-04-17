/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : Alexander Achorn
Author : UE4
*/

#include "RCRacingGameMode.h"
#include "../Pawns/RCRacingPawn.h"
#include "../UI/RCRacingHud.h"

ARCRacingGameMode::ARCRacingGameMode()
{
	DefaultPawnClass = ARCRacingPawn::StaticClass();
	HUDClass = ARCRacingHud::StaticClass();
}
