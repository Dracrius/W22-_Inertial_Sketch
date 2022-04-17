/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : Alexander Achorn
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RCRacingHud.generated.h"

//Will Get Scrapped in Favor of our Own HUD
UCLASS(config = Game)
class ARCRacingHud : public AHUD
{
	GENERATED_BODY()

public:
	ARCRacingHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
