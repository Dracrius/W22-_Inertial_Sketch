// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RCRacingHud.generated.h"

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
