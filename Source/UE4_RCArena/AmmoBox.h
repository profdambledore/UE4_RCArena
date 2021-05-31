// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBox.h"

#include "AmmoBox.generated.h"

class ABasePickup;

UCLASS()
class UE4_RCARENA_API AAmmoBox : public ABaseBox
{
	GENERATED_BODY()
	
public:
	AAmmoBox();

	virtual void BreakBox() override;

	int MaxSpawns = 5;
	int MinSpawns = 3;

	TSubclassOf<ABasePickup> PickupToSpawn = nullptr;
};
