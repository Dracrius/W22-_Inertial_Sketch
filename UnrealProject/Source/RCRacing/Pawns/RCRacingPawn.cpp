/*
Copyright 2022 Inertial Sketch
Copyright 2022 Antoine Plouffe <antoine.plouffe1@gmail.com>
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Antoine Plouffe
Author : Alexander Achorn
Author : UE4

Changelog:
3/18
Added VR Support
3/19
Added More Comments
3/28
Started Networking Adaptations
3/29
Fixed Networked Player Controls
4/7
Completed Networking Adaptations
*/

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
#include "RCRacing/Actors/Firework_PowerUp.h"
#include "RCRacing/Actors/Freeze_PowerUp.h"
#include "RCRacing/Actors/Trap_PowerUp.h"
#include "../GameStates/RCGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "../UI/InGameUI.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "RacingPlayerState.h"

#include <string>

const FName ARCRacingPawn::LookUpBinding("LookUp");
const FName ARCRacingPawn::LookRightBinding("LookRight");
const FName ARCRacingPawn::EngineAudioRPM("RPM");

#define LOCTEXT_NAMESPACE "VehiclePawn"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

ARCRacingPawn::ARCRacingPawn()
{
    for (int i = 0; i < 3; i++)
    {
        std::string name = "Car Body Mesh " + std::to_string(i);
        //mesh
        UStaticMeshComponent* CarBodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(name.c_str());
        //Rotating the Mesh
        CarBodyMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
        //No collision
        CarBodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        //Make Invisible
        CarBodyMesh->SetVisibility(false);
        //Location at 0
        CarBodyMesh->SetRelativeLocation(FVector(0));
        //attach the mesh to RootComponent 
        CarBodyMesh->SetupAttachment(RootComponent);

        CarBodyMeshs.Add(CarBodyMesh);
    }

	// Car mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/VehicleAdv/Vehicle/Vehicle_SkelMesh.Vehicle_SkelMesh"));
	GetMesh()->SetSkeletalMesh(CarMesh.Object);
	
	static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/VehicleAdv/Vehicle/VehicleAnimationBlueprint"));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(AnimBPClass.Class);

	// Setup friction materials
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> SlipperyMat(TEXT("/Game/VehicleAdv/PhysicsMaterials/Slippery.Slippery"));
	SlipperyMaterial = SlipperyMat.Object;
		
	static ConstructorHelpers::FObjectFinder<UPhysicalMaterial> NonSlipperyMat(TEXT("/Game/VehicleAdv/PhysicsMaterials/NonSlippery.NonSlippery"));
	NonSlipperyMaterial = NonSlipperyMat.Object;

	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4);

	// Wheels/Tyres
	// Setup the wheels
	Vehicle4W->WheelSetups[0].WheelClass = URCRacingWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("PhysWheel_FL");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -8.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = URCRacingWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("PhysWheel_FR");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 8.f, 0.f);

	Vehicle4W->WheelSetups[2].WheelClass = URCRacingWheelRear::StaticClass();
	Vehicle4W->WheelSetups[2].BoneName = FName("PhysWheel_BL");
	Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -8.f, 0.f);

	Vehicle4W->WheelSetups[3].WheelClass = URCRacingWheelRear::StaticClass();
	Vehicle4W->WheelSetups[3].BoneName = FName("PhysWheel_BR");
	Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 8.f, 0.f);

	// Adjust the tire loading
	Vehicle4W->MinNormalizedTireLoad = 0.0f;
	Vehicle4W->MinNormalizedTireLoadFiltered = 0.2f;
	Vehicle4W->MaxNormalizedTireLoad = 2.0f;
	Vehicle4W->MaxNormalizedTireLoadFiltered = 2.0f;

	// Engine 
	// Torque setup
	Vehicle4W->MaxEngineRPM = 5700.0f;
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 400.0f);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1890.0f, 500.0f);
	Vehicle4W->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(5730.0f, 400.0f);
	// Adjust the steering 
	Vehicle4W->SteeringCurve.GetRichCurve()->Reset();
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(0.0f, 1.0f);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(40.0f, 0.7f);
	Vehicle4W->SteeringCurve.GetRichCurve()->AddKey(120.0f, 0.6f);
 	// Transmission	
	// We want 4wd
	Vehicle4W->DifferentialSetup.DifferentialType = EVehicleDifferential4W::LimitedSlip_4W;
	
	// Drive the front wheels a little more than the rear
	Vehicle4W->DifferentialSetup.FrontRearSplit = 0.65;

	// Automatic gearbox
	Vehicle4W->TransmissionSetup.bUseGearAutoBox = true;
	Vehicle4W->TransmissionSetup.GearSwitchTime = 0.15f;
	Vehicle4W->TransmissionSetup.GearAutoBoxLatency = 1.0f;

	// Physics settings
	// Adjust the center of mass - the buggy is quite low
	UPrimitiveComponent* UpdatedPrimitive = Cast<UPrimitiveComponent>(Vehicle4W->UpdatedComponent);
	if (UpdatedPrimitive)
	{
		UpdatedPrimitive->BodyInstance.COMNudge = FVector(8.0f, 0.0f, 0.0f);
	}

	// Set the inertia scale. This controls how the mass of the vehicle is distributed.
	Vehicle4W->InertiaTensorScale = FVector(1.0f, 1.333f, 1.2f);

	// Create a spring arm component for our chase camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 34.0f));
	SpringArm->SetWorldRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 125.0f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	// Create the chase camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ChaseCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetRelativeLocation(FVector(-125.0, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(10.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	// Create In-Car camera component 
	InternalCameraOrigin = FVector(-34.0f, -10.0f, 50.0f);
	InternalCameraBase = CreateDefaultSubobject<USceneComponent>(TEXT("InternalCameraBase"));
	InternalCameraBase->SetRelativeLocation(InternalCameraOrigin);
	InternalCameraBase->SetupAttachment(GetMesh());

    // Create a HMD Function Library
    HMDFunctions = CreateDefaultSubobject<UHeadMountedDisplayFunctionLibrary>(TEXT("HMDFunctions"));

	//InternalCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("InternalCamera"));
	//InternalCamera->bUsePawnControlRotation = false;
	//InternalCamera->FieldOfView = 90.f;
	//InternalCamera->SetupAttachment(InternalCameraBase);

	// In car HUD
	// Create text render component for in car speed display
	InCarSpeed = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarSpeed"));
	InCarSpeed->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	InCarSpeed->SetRelativeLocation(FVector(35.0f, -6.0f, 20.0f));
	InCarSpeed->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InCarSpeed->SetupAttachment(GetMesh());

	// Create text render component for in car gear display
	InCarGear = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	InCarGear->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	InCarGear->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	InCarGear->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
	InCarGear->SetupAttachment(GetMesh());
	
	// Setup the audio component and allocate it a sound cue
	static ConstructorHelpers::FObjectFinder<USoundCue> SoundCue(TEXT("/Game/VehicleAdv/Sound/Engine_Loop_Cue.Engine_Loop_Cue"));
	EngineSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineSound"));
	EngineSoundComponent->SetSound(SoundCue.Object);
	EngineSoundComponent->SetupAttachment(GetMesh());

	// Colors for the in-car gear display. One for normal one for reverse
	GearDisplayReverseColor = FColor(255, 0, 0, 255);
	GearDisplayColor = FColor(255, 255, 255, 255);

	bIsLowFriction = false;
	bInReverseGear = false;

    SetReplicates(true);
    SetReplicateMovement(true);

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ARCRacingPawn::OnOverlapBegin);
}

void ARCRacingPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARCRacingPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARCRacingPawn::MoveRight);
	PlayerInputComponent->BindAxis(LookUpBinding);
	PlayerInputComponent->BindAxis(LookRightBinding);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ARCRacingPawn::Pause);

	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ARCRacingPawn::OnToggleCamera);

	PlayerInputComponent->BindAction("UsePowerUp", IE_Pressed, this, &ARCRacingPawn::ServerOnUsePowerUp);

    // VR headset functionality
    PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ARCRacingPawn::OnResetVR);
}

//Pause Menu
void ARCRacingPawn::Pause()
{
	static_cast<ARCGameStateBase*>(GetWorld()->GetGameState())->isPaused = true;

	static_cast<AInGameUI*>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD())->ShowPauseMenu();
}

//Movements
void ARCRacingPawn::MoveForward(float Val)
{
	if (GetWorld() && GetWorld()->GetGameState())
	{
		if (!static_cast<ARCGameStateBase*>(GetWorld()->GetGameState())->isPaused)
		{
			GetVehicleMovementComponent()->SetThrottleInput(Val);
		}
	}
}

void ARCRacingPawn::MoveRight(float Val)
{
	if (GetWorld() && GetWorld()->GetGameState())
	{
		if (!static_cast<ARCGameStateBase*>(GetWorld()->GetGameState())->isPaused)
		{
			GetVehicleMovementComponent()->SetSteeringInput(Val);
		}
	}
}

void ARCRacingPawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void ARCRacingPawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void ARCRacingPawn::OnToggleCamera()
{
	EnableIncarView(!bInCarCameraActive);
}

void ARCRacingPawn::EnableIncarView(const bool bState)
{
	if (bState != bInCarCameraActive)
	{
		bInCarCameraActive = bState;
		
		if (bState == true)
		{
			Camera->Deactivate();
			InternalCamera->Activate();
		}
		else
		{
			InternalCamera->Deactivate();
			Camera->Activate();
		}
		
		InCarSpeed->SetVisibility(bInCarCameraActive);
		InCarGear->SetVisibility(bInCarCameraActive);
	}
}

void ARCRacingPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	// Setup the flag to say we are in reverse gear
	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;
	
	// Update phsyics material
	UpdatePhysicsMaterial();

	// Update the strings used in the hud (incar and onscreen)
	UpdateHUDStrings();

	// Set the string in the incar hud
	SetupInCarHUD();

	bool bHMDActive = false;

	if( bHMDActive == false )
	{
		if ( (InputComponent) && (bInCarCameraActive == true ))
		{
			FRotator HeadRotation = InternalCamera->GetRelativeRotation();
			HeadRotation.Pitch += InputComponent->GetAxisValue(LookUpBinding);
			HeadRotation.Yaw += InputComponent->GetAxisValue(LookRightBinding);
			InternalCamera->SetRelativeRotation(HeadRotation);
		}
	}	

	// Pass the engine RPM to the sound component
	float RPMToAudioScale = 2500.0f / GetVehicleMovement()->GetEngineMaxRotationSpeed();
	EngineSoundComponent->SetFloatParameter(EngineAudioRPM, GetVehicleMovement()->GetEngineRotationSpeed()*RPMToAudioScale);

	//Powerups
	if (IsLocallyControlled() )//This is the AUtonomous_Proxy Client
	{
		if(InputComponent)
		{
			FMovementData mv;
			mv.MovementForward = InputComponent->GetAxisValue("MoveForward");
			mv.MovementRight = -InputComponent->GetAxisValue("MoveRight");
			Server_CallFlipCar(mv);
		}
	}
}
void ARCRacingPawn::Server_CallFlipCar_Implementation(FMovementData mvData)
{
	MovementDataStruct = mvData;
	bNotGrounded = FVector::DotProduct(GetActorUpVector(), FVector::UpVector) < 0.1f;

	if (bNotGrounded == false)
	{
		MovementDataStruct.MovementForward = 0.0f;
		MovementDataStruct.MovementRight = 0.0f;
	}

	OnRepFlipCar();
}

void ARCRacingPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARCRacingPawn, MovementDataStruct);
}

//prevents the player getting their vehicle upside down and/or stuck
void ARCRacingPawn::OnRepFlipCar()
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
	{
		FlipForceAmount = 50.0f;
	}
	else
	{
		FlipForceAmount = 200.0f;
	}


	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	if (KPH_int == 0)
	{
		if (UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
		{
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			//TraceStart: where the LineTrace starts in the Z Axis;
			//TraceEnd: where the LineTrace ends in the Z Axis.
			const FVector TraceStart = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);
			const FVector TraceEnd = GetActorLocation() + FVector(0.0f, 0.0f, 200.0f);

			FHitResult Hit;

			//bInAir uses LineTraceSingleByChannel to detect if the player is currently in the air;
			//bNotGrounded uses a DotProduct to detect if the player’s up vector is parallel to an UpVector
			const bool bInAir = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

			if (bNotGrounded)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Red, FString::Printf(TEXT("Mv F = %d, Mv R = %d"), MovementDataStruct.MovementForward, MovementDataStruct.MovementRight));
				const float RightInput = MovementDataStruct.MovementRight;

				const float FlipAirMovementForceRoll = !bInAir && bNotGrounded ? 15.0f : 2.0f;

				if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
				{
					//flip the car until it is grounded.
					const FVector MovementVector = FVector(RightInput * FlipAirMovementForceRoll, 0.0f, 0.0f) * FApp::GetDeltaTime() * FlipForceAmount;
					const FVector NewAngularMovement = GetActorRotation().RotateVector(MovementVector);
					VehicleMesh->SetPhysicsAngularVelocity(NewAngularMovement, true);
				}
			}
		}
	}

}

void ARCRacingPawn::BeginPlay()
{
	Super::BeginPlay();

    ARacingPlayerState* playerState = Cast<ARacingPlayerState>(GetPlayerState());
    if (playerState)
    {
        CarBodyMeshs[playerState->CarBodySelection]->SetVisibility(true);
    }

    if (HMDFunctions->IsHeadMountedDisplayEnabled())
    {
        HMDFunctions->SetTrackingOrigin(EHMDTrackingOrigin::Eye);

        Camera->bLockToHmd = true;
        Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

        SpringArm->bInheritPitch = false;
        SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
        SpringArm->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
        SpringArm->TargetArmLength = 200.0f;

    }

	bool bWantInCar = false;
	// First disable both speed/gear displays 
	bInCarCameraActive = false;
	InCarSpeed->SetVisibility(bInCarCameraActive);
	InCarGear->SetVisibility(bInCarCameraActive);

	// Enable in car view if HMD is attached
	EnableIncarView(bWantInCar);
	// Start an engine sound playing
	EngineSoundComponent->Play();

	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());
	UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive;

	VehicleMesh->SetIsReplicated(true);
}

void ARCRacingPawn::OnResetVR()
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ARCRacingPawn::UpdateHUDStrings()
{
	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);
	int32 Gear = GetVehicleMovement()->GetCurrentGear();

	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));


	if (bInReverseGear == true)
	{
		GearDisplayString = FText(LOCTEXT("ReverseGear", "R"));
	}
	else
	{
		GearDisplayString = (Gear == 0) ? LOCTEXT("N", "N") : FText::AsNumber(Gear);
	}

}

//switch a few settings and is to call the virtual Use function of the PowerUp class.
//autority to spawn the power ups
void ARCRacingPawn::ServerOnUsePowerUp_Implementation()
{
	if (PowerupClass)
	{
		if (CurrentPowerUp)
		{

			CurrentPowerUp->SetActive(true);
			CurrentPowerUp->SetUsed(true);
			CurrentPowerUp->SetActorEnableCollision(true);
			CurrentPowerUp->SetActorHiddenInGame(false);
			FVector spawnPosition;

			if (Cast<ABowlingBall_PowerUp>(CurrentPowerUp) || Cast<ATrap_PowerUp>(CurrentPowerUp))
			{
				//CurrentPowerUp->SetActorEnableCollision(true);
				float offsetX = GetActorForwardVector().X * -200.0f;
				float offsetY = GetActorForwardVector().Y * -200.0f;
				float offsetZ = 40.0f;

				FVector offset = FVector(offsetX, offsetY, offsetZ);

				spawnPosition = GetActorLocation() + offset;
			}
			else
			{
				float offsetX = GetActorForwardVector().X * 200.0f;
				float offsetY = GetActorForwardVector().Y * 200.0f;
				float offsetZ = 40.0f;

				FVector offset = FVector(offsetX, offsetY, offsetZ);

				spawnPosition = GetActorLocation() + offset;
			}

			CurrentPowerUp->Use(GetActorForwardVector(), spawnPosition);
			CurrentPowerUp = nullptr;
		}
	}
}

//sets the player’s current power up to the randomly chosen one inside the PowerUp class. 
void ARCRacingPawn::SetCurrentPowerUp(int power)
{
	if (CurrentPowerUp != nullptr)
	{
		CurrentPowerUp->SetActorHiddenInGame(true);
		CurrentPowerUp->SetActorEnableCollision(false);
		CurrentPowerUp->SetMeshToNull();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (power == 1)
	{
		BowlingBall_PowerUp = GetWorld()->SpawnActor<APowerUp>(BowlingBall_PowerUpClass, FVector(0), FRotator::ZeroRotator, SpawnParams);

		CurrentPowerUp = BowlingBall_PowerUp;

		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Current Power: Bowling Ball!"));
	}
	else if (power == 2)
	{
		Firework_PowerUp = GetWorld()->SpawnActor<APowerUp>(Firework_PowerUpClass, FVector(0), FRotator::ZeroRotator, SpawnParams);

		CurrentPowerUp = Firework_PowerUp;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Current Power: Firework!"));
	}
	else if (power == 3)
	{
		Freeze_PowerUp = GetWorld()->SpawnActor<APowerUp>(Freeze_PowerUpClass, FVector(0), FRotator::ZeroRotator, SpawnParams);
		
		CurrentPowerUp = Freeze_PowerUp;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Current Power: Freeze!"));
	}
	else if (power == 4)
	{
		Trap_PowerUp = GetWorld()->SpawnActor<APowerUp>(Trap_PowerUpClass, FVector(0), FRotator::ZeroRotator, SpawnParams);

		CurrentPowerUp = Trap_PowerUp;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Current Power: Trap!"));
	}

	CurrentPowerUp->SetPicked(true);
	CurrentPowerUp->SetActorHiddenInGame(true);
}

void ARCRacingPawn::Server_CallTrapped_Implementation(AWheeledVehicle* ActorTrapped)
{
	OnRepTrapped(ActorTrapped);
}

//creates a wow moment when the player overlaps a trap by moving upwards and rotating their vehicle mesh
void ARCRacingPawn::OnRepTrapped(AWheeledVehicle* ActorTrapped)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You've been trapped!"));

	if (UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(ActorTrapped->GetVehicleMovement()))
	{
		if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
		{
			const FVector MovementVector = FVector(AirMovementForceRoll, 0.0f, 0.0f);
			const FVector NewAngularMovement = GetActorRotation().RotateVector(MovementVector);
			VehicleMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 1000.f), true);
			VehicleMesh->SetPhysicsAngularVelocity(NewAngularMovement, true);
		}
	}
}

void ARCRacingPawn::Server_CallFreezed_Implementation(float deltaTime)
{
	OnRepFreezed(deltaTime);
}

//applies the freeze effect on the vehicle mesh.
void ARCRacingPawn::OnRepFreezed(float deltaTime)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You've been freezed!"));

	if (UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
	{
		if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
		{
			VehicleMesh->SetPhysicsLinearVelocity(FVector(0), false);
		}
	}
}

void ARCRacingPawn::Server_CallGotHit_Implementation()
{
	OnRepGotHit();
}

//temporarily paralyzed the player’s vehicle OnHit.
void ARCRacingPawn::OnRepGotHit()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You've been hit!"));
	if (UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
	{
		if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
		{
			VehicleMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 500.0f), false);
		}
	}
}

void ARCRacingPawn::Server_CallBoost_Implementation()
{
	OnRepBoost();
}

//temporarily boost the player’s vehicle speed.
void ARCRacingPawn::OnRepBoost()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Boost!"));
	if (UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement()))
	{
		if (UPrimitiveComponent* VehicleMesh = Vehicle4W->UpdatedPrimitive)
		{
			FVector Force = GetActorForwardVector() * BoostAmount;
			VehicleMesh->SetPhysicsLinearVelocity(Force, true);
		}
	}
}

void ARCRacingPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    //Game will fail to build without. This is used for powerups!
}


void ARCRacingPawn::SetupInCarHUD()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if ((PlayerController != nullptr) && (InCarSpeed != nullptr) && (InCarGear != nullptr))
	{
		// Setup the text render component strings
		InCarSpeed->SetText(SpeedDisplayString);
		InCarGear->SetText(GearDisplayString);
		
		if (bInReverseGear == false)
		{
			InCarGear->SetTextRenderColor(GearDisplayColor);
		}
		else
		{
			InCarGear->SetTextRenderColor(GearDisplayReverseColor);
		}
	}
}

void ARCRacingPawn::UpdatePhysicsMaterial()
{
	if (GetActorUpVector().Z < 0)
	{
		if (bIsLowFriction == true)
		{
			GetMesh()->SetPhysMaterialOverride(NonSlipperyMaterial);
			bIsLowFriction = false;
		}
		else
		{
			GetMesh()->SetPhysMaterialOverride(SlipperyMaterial);
			bIsLowFriction = true;
		}
	}
}

#undef LOCTEXT_NAMESPACE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
