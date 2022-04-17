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

    virtual void OnPossess(APawn* aPawn) override;
    virtual void OnUnPossess() override;

    // End Actor interface
    virtual void Pause();

    /** Handle pressing forwards */
    virtual void MoveForward(float Val);

    /** Handle pressing right */
    virtual void MoveRight(float Val);

    //switch a few settings and is to call the virtual Use function of the PowerUp class
    UFUNCTION(Server, Reliable)
    virtual void ServerOnUsePowerUp();

    static const FName LookUpBinding;
    static const FName LookRightBinding;

protected:
    virtual void SetupInputComponent() override;

    /** Resets HMD orientation in VR. */
    virtual void OnResetVR();

    class ARCRacingPawn* MyPawn;
	
};
