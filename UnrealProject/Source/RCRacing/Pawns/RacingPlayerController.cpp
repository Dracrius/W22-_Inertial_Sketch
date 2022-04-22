/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4

Changelog:
4/16
Added Custom PlayerController
*/


#include "RacingPlayerController.h"
#include "RCRacingPawn.h"
#include "Components/InputComponent.h"

//Set The Const Names For Lookup
const FName ARacingPlayerController::LookUpBinding("LookUp");
const FName ARacingPlayerController::LookRightBinding("LookRight");

/** Handle Pawn Possesion */
void ARacingPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);
    //File Pawn Pointer
    MyPawn = Cast<ARCRacingPawn>(aPawn);
}

/** Handle Pawn UnPosses */
void ARacingPlayerController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());

    Super::OnUnPossess();
}

/** Open Pause Menu  */
void ARacingPlayerController::Pause()
{
    //Use Pawns Pause
    if (MyPawn)
        MyPawn->Pause();
}

/** Handle Forward and Backwards */
void ARacingPlayerController::MoveForward(float Val)
{
    //Use Pawns MoveForward
    if (MyPawn)
        MyPawn->MoveForward(Val);
}

/** Handle Turning */
void ARacingPlayerController::MoveRight(float Val)
{
    //Use Pawns MoveRight
    if (MyPawn)
        MyPawn->MoveRight(Val);
}

//switch a few settings and is to call the virtual Use function of the PowerUp class
void ARacingPlayerController::ServerOnUsePowerUp_Implementation()
{
    //Use Pawns OnUsePowerUp
    if (MyPawn)
        MyPawn->ServerOnUsePowerUp();
}

/** Setup input Comp */
void ARacingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //Check that InputComp isn't Null
    if (InputComponent != nullptr)
    {
        //Bind Movement
        InputComponent->BindAxis("MoveForward", this, &ARacingPlayerController::MoveForward);
        InputComponent->BindAxis("MoveRight", this, &ARacingPlayerController::MoveRight);
        InputComponent->BindAxis(LookUpBinding);
        InputComponent->BindAxis(LookRightBinding);

        //Bind Pause Menu
        InputComponent->BindAction("Pause", IE_Pressed, this, &ARacingPlayerController::Pause);

        //Bind Use Powerup
        InputComponent->BindAction("UsePowerUp", IE_Pressed, this, &ARacingPlayerController::ServerOnUsePowerUp);

        // VR headset functionality
        InputComponent->BindAction("ResetVR", IE_Pressed, this, &ARacingPlayerController::OnResetVR);
    }
}

/** Resets HMD orientation in VR. */
void ARacingPlayerController::OnResetVR()
{
    //Use Pawns OnResetVR
    if (MyPawn)
        MyPawn->OnResetVR();
}
