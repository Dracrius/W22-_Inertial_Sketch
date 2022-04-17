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
#include "RCRacingWheelFront.h"
#include "RCRacingWheelRear.h"
#include "../UI/RCRacingHud.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Components/BoxComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "GameFramework/Controller.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "RCRacing/Actors/BowlingBall_PowerUp.h"
#include "RCRacing/Actors/PowerUp.h"
#include "Editor/UnrealEd/Classes/Editor/EditorEngine.h"
#include "RCRacing/Actors/Firework_PowerUp.h"
#include "RCRacing/Actors/Freeze_PowerUp.h"
#include "RCRacing/Actors/Trap_PowerUp.h"
#include "../GameStates/RCGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/InGameUI.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

const FName ARacingPlayerController::LookUpBinding("LookUp");
const FName ARacingPlayerController::LookRightBinding("LookRight");

void ARacingPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    MyPawn = Cast<ARCRacingPawn>(aPawn);
}

void ARacingPlayerController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());

    Super::OnUnPossess();
}

void ARacingPlayerController::Pause()
{
    if (MyPawn)
        MyPawn->Pause();
}

void ARacingPlayerController::MoveForward(float Val)
{
    if (MyPawn)
        MyPawn->MoveForward(Val);
}

void ARacingPlayerController::MoveRight(float Val)
{
    if (MyPawn)
        MyPawn->MoveRight(Val);
}

void ARacingPlayerController::ServerOnUsePowerUp_Implementation()
{
    if (MyPawn)
        MyPawn->ServerOnUsePowerUp();
}

void ARacingPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (InputComponent != nullptr)
    {
        InputComponent->BindAxis("MoveForward", this, &ARacingPlayerController::MoveForward);
        InputComponent->BindAxis("MoveRight", this, &ARacingPlayerController::MoveRight);
        InputComponent->BindAxis(LookUpBinding);
        InputComponent->BindAxis(LookRightBinding);

        InputComponent->BindAction("Pause", IE_Pressed, this, &ARacingPlayerController::Pause);

        InputComponent->BindAction("UsePowerUp", IE_Pressed, this, &ARacingPlayerController::ServerOnUsePowerUp);

        // VR headset functionality
        InputComponent->BindAction("ResetVR", IE_Pressed, this, &ARacingPlayerController::OnResetVR);
    }
}

void ARacingPlayerController::OnResetVR()
{
    if (MyPawn)
        MyPawn->OnResetVR();
}
