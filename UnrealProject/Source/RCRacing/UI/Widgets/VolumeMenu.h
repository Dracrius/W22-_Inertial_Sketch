/*
Copyright 2022 Inertial Sketch
Copyright 2022 Alexander Achorn <a.achorn@gmail.com>
Version: 0.2
Author : Alexander Achorn
Author : UE4
*/

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "VolumeMenu.generated.h"

//The Volume Menu
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
