/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4
*/

#pragma once

#include "RCRacingPawn.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RacingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API ARacingPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    /** Handle Pawn Possesion */
    virtual void OnPossess(APawn* aPawn) override;
    /** Handle Pawn UnPosses */
    virtual void OnUnPossess() override;

    /** Open Pause Menu  */
    virtual void Pause();

    /** Handle Forward and Backwards */
    virtual void MoveForward(float Val);

    /** Handle Turning */
    virtual void MoveRight(float Val);

    //switch a few settings and is to call the virtual Use function of the PowerUp class
    UFUNCTION(Server, Reliable)
    virtual void ServerOnUsePowerUp();

    // Binding Names for Lookup
    static const FName LookUpBinding;
    static const FName LookRightBinding;

protected:
    /** Setup input Comp */
    virtual void SetupInputComponent() override;

    /** Resets HMD orientation in VR. */
    virtual void OnResetVR();

    /** To Store the Players Pawn */
    class ARCRacingPawn* MyPawn;
	
};
