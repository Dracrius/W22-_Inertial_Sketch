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
#include "UsernameMenu.generated.h"

//The Username Entry Menu
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

public:
	UFUNCTION(BlueprintCallable)
	virtual void Return();

	UFUNCTION(BlueprintCallable)
	virtual void SetName(FText name);	
};
