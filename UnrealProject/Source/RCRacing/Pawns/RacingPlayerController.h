// Fill out your copyright notice in the Description page of Project Settings.

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
    void Pause();

    /** Handle pressing forwards */
    void MoveForward(float Val);

    /** Handle pressing right */
    void MoveRight(float Val);

    //switch a few settings and is to call the virtual Use function of the PowerUp class
    UFUNCTION(Server, Reliable)
    void ServerOnUsePowerUp();

    static const FName LookUpBinding;
    static const FName LookRightBinding;

protected:
    virtual void SetupInputComponent() override;

    virtual void AcknowledgePossession(APawn* PossesedPawn) override;

    /** Resets HMD orientation in VR. */
    void OnResetVR();

    class ARCRacingPawn* MyPawn;
	
};
