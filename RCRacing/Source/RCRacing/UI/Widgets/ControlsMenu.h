// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "ControlsMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API UControlsMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UFont* menuFont;

protected:
	UControlsMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void Return();

public:
	
};
