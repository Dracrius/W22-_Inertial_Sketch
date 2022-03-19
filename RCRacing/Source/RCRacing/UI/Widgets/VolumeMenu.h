// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "VolumeMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API UVolumeMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UFont* menuFont;

	float musicVolume;
	float effectVolume;

protected:
	UVolumeMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Return();

	UFUNCTION(BlueprintCallable)
	virtual void ReturnToMain();

	UFUNCTION(BlueprintCallable)
	virtual void SetVolume(FText channel, float vol);
	
};
