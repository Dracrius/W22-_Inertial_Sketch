/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : UE4
*/

#include "RCRacingWheelFront.h"
#include "TireConfig.h"
#include "UObject/ConstructorHelpers.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

URCRacingWheelFront::URCRacingWheelFront()
{
	ShapeRadius = 18.f;
	ShapeWidth = 15.0f;
	bAffectedByHandbrake = false;
	SteerAngle = 40.f;

	// Setup suspension forces
	SuspensionForceOffset = -4.0f;
	SuspensionMaxRaise = 8.0f;
	SuspensionMaxDrop = 12.0f;
	SuspensionNaturalFrequency = 9.0f;
	SuspensionDampingRatio = 1.05f;

	// Find the tire object and set the data for it
	static ConstructorHelpers::FObjectFinder<UTireConfig> TireData(TEXT("/Game/VehicleAdv/Vehicle/WheelData/Vehicle_FrontTireConfig.Vehicle_FrontTireConfig"));
	TireConfig = TireData.Object;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
