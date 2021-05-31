// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "WeaponTargetWidget.generated.h"


UCLASS()
class UE4_RCARENA_API UWeaponTargetWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

public:
	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* TargetIcon = nullptr;
};
