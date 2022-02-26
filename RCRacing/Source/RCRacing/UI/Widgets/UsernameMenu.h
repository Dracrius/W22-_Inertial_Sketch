// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include "Blueprint/UserWidget.h"
#include "UsernameMenu.generated.h"

/**
 * 
 */
UCLASS()
class RCRACING_API UUsernameMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UFont* menuFont;

	FText playerName;

protected:
	UUsernameMenu(const FObjectInitializer& rootMenu);

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void Return();

	UFUNCTION()
	virtual void SetName(FText name);

public:
	
};