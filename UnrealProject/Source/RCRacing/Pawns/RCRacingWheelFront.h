/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include "VehicleWheel.h"
#include "RCRacingWheelFront.generated.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UCLASS()
class URCRacingWheelFront : public UVehicleWheel
{
	GENERATED_BODY()

public:
	URCRacingWheelFront();
};

PRAGMA_ENABLE_DEPRECATION_WARNINGS
