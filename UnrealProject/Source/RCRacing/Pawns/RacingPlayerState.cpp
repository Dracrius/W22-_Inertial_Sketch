// Fill out your copyright notice in the Description page of Project Settings.


#include "RacingPlayerState.h"
#include "Net/UnrealNetwork.h"

ARacingPlayerState::ARacingPlayerState()
{
    CarBodySelection = FMath::RandRange(0, 3 - 1);
}

void ARacingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ARacingPlayerState, CarBodySelection);
}