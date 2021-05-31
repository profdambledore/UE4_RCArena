// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBox.h"

#include "HealthBox.generated.h"

class ABasePickup;

UCLASS()
class UE4_RCARENA_API AHealthBox : public ABaseBox
{
	GENERATED_BODY()

public:
	AHealthBox();

	virtual void BreakBox() override;

	int MaxSpawns = 3;
	int MinSpawns = 1;

	TSubclassOf<ABasePickup> PickupToSpawn = nullptr;
};
