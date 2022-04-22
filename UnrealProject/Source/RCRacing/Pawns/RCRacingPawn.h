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
#include "WheeledVehicle.h"
#include "RCRacingPawn.generated.h"

class AFirework_PowerUp;
class AFreeze_PowerUp;
class ATrap_PowerUp;
class ABowlingBall_PowerUp;
class UBoxComponent;
class APowerUp;
class UPhysicalMaterial;
class UCameraComponent;
class USpringArmComponent;
class UTextRenderComponent;
class UInputComponent;
class UAudioComponent;

PRAGMA_DISABLE_DEPRECATION_WARNINGS


USTRUCT(BlueprintType)
struct FMovementData
{
	GENERATED_BODY()

public:
	FMovementData(){}

	UPROPERTY()
	float MovementForward;

	UPROPERTY()
	float MovementRight;
};

UCLASS(config=Game)
class ARCRacingPawn : public AWheeledVehicle
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category = "Car Bodies")
        TArray<UStaticMeshComponent*> CarBodyMeshs;

		/** Spring arm that will offset the camera */
    UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	/** SCene component for the In-Car view origin */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* InternalCameraBase;

	/** Camera component for the In-Car view */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* InternalCamera;

	/** Text component for the In-Car speed */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* InCarSpeed;

	/** Text component for the In-Car gear */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UTextRenderComponent* InCarGear;

	/** Audio component for the engine sound */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* EngineSoundComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UHeadMountedDisplayFunctionLibrary* HMDFunctions;

public:
	ARCRacingPawn();

	/** The current speed as a string eg 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText SpeedDisplayString;

	/** The current gear as a string (R,N, 1,2 etc) */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText GearDisplayString;

	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		/** The color of the incar gear text in forward gears */
		FColor	GearDisplayColor;

	/** The color of the incar gear text when in reverse */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FColor	GearDisplayReverseColor;

	/** Are we using incar camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		bool bInCarCameraActive;

	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		bool bInReverseGear;

	/** Initial offset of incar camera */
	FVector InternalCameraOrigin;

	UPROPERTY(ReplicatedUsing = OnRepFlipCar)
		FMovementData MovementDataStruct;

	UFUNCTION(Server, Unreliable)
		void Server_CallFlipCar(FMovementData mvData);

	//Flips the car on inputkey when upside down
	UFUNCTION()
		void OnRepFlipCar();

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	// Begin Actor interface
	virtual void Tick(float Delta) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    /** Resets HMD orientation in VR. */
    void OnResetVR();

	// End Actor interface
	void Pause();

	/** Handle pressing forwards */
	void MoveForward(float Val);

	/** Setup the strings used on the hud */
	void SetupInCarHUD();

	/** Update the physics material used by the vehicle mesh */
	void UpdatePhysicsMaterial();

	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();
	/** Switch between cameras */
	void OnToggleCamera();

	static const FName LookUpBinding;
	static const FName LookRightBinding;
	static const FName EngineAudioRPM;

private:

	void EnableIncarView( const bool bState );

	/** Update the gear and speed strings */
	void UpdateHUDStrings();

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;
	/** Slippery Material instance */
	UPhysicalMaterial* SlipperyMaterial;
	/** Non Slippery Material instance */
	UPhysicalMaterial* NonSlipperyMaterial;


public:
	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	/** Returns InternalCamera subobject **/
	FORCEINLINE UCameraComponent* GetInternalCamera() const { return InternalCamera; }
	/** Returns InCarSpeed subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarSpeed() const { return InCarSpeed; }
	/** Returns InCarGear subobject **/
	FORCEINLINE UTextRenderComponent* GetInCarGear() const { return InCarGear; }
	/** Returns EngineSoundComponent subobject **/
	FORCEINLINE UAudioComponent* GetEngineSoundComponent() const { return EngineSoundComponent; }

public:

	//Power Up section
	bool bNotGrounded;

	//switch a few settings and is to call the virtual Use function of the PowerUp class
	UFUNCTION(Server, Reliable)
		void ServerOnUsePowerUp();

	//These variables are used inside UE4 to sets the power ups inside this class' blueprint
	UPROPERTY(EditAnywhere, Category = "PowerUp Blueprint")
		TSubclassOf<APowerUp> PowerupClass;

	UPROPERTY(EditAnywhere, Category = "PowerUp Blueprint")
		TSubclassOf<APowerUp> BowlingBall_PowerUpClass;

	UPROPERTY(EditAnywhere, Category = "PowerUp Blueprint")
		TSubclassOf<APowerUp> Firework_PowerUpClass;

	UPROPERTY(EditAnywhere, Category = "PowerUp Blueprint")
		TSubclassOf<APowerUp> Freeze_PowerUpClass;

	UPROPERTY(EditAnywhere, Category = "PowerUp Blueprint")
		TSubclassOf<APowerUp> Trap_PowerUpClass;

	//Use by the player on InputKey to use the player's current power up
	UPROPERTY(EditAnywhere, Category = "PowerUp")
		APowerUp* CurrentPowerUp = nullptr;

	//Use to set CurrentPowerUp to this 
	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
		APowerUp* BowlingBall_PowerUp;

	//Use to set CurrentPowerUp to this 
	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
		APowerUp* Firework_PowerUp;

	//Use to set CurrentPowerUp to this 
	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
		APowerUp* Freeze_PowerUp;

	//Use to set CurrentPowerUp to this 
	UPROPERTY(EditDefaultsOnly, Category = "PowerUp")
		APowerUp* Trap_PowerUp;

	//Boost amount for when the vehicle overlaps the boost pad
	UPROPERTY(EditAnywhere, Category = "PowerUp")
		int BoostAmount = 1000.0f;

	//Roll force for the Trap
	UPROPERTY(EditAnywhere, Category = "PowerUp")
		float AirMovementForceRoll = 250.0f;

	float FlipForceAmount;

	//Called by the PowerUp parent class to randomly assign a power up to CurrentPowerUp
	void SetCurrentPowerUp(int power);

	//Called by the Trap PowerUp on overlap
	UFUNCTION(Server, Unreliable)
		void Server_CallTrapped(AWheeledVehicle* ActorTrapped);

	UFUNCTION()
		void OnRepTrapped(AWheeledVehicle* ActorTrapped);

	//Called by the Freeze PowerUp when the vehicle is in the effect radius

	UFUNCTION(Server, Unreliable)
		void Server_CallFreezed(float deltaTime);

	UFUNCTION()
		void OnRepFreezed(float deltaTime);

	//

	UFUNCTION(Server, Unreliable)
		void Server_CallGotHit();

	UFUNCTION()
		void OnRepGotHit();

	//Called by the Boost class on overlap
	UFUNCTION(Server, Unreliable)
		void Server_CallBoost();

	UFUNCTION()
		void OnRepBoost();
};

PRAGMA_ENABLE_DEPRECATION_WARNINGS
