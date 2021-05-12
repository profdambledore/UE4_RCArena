// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseBox.h"

#include "MoneyBox.generated.h"

class ABasePickup;

UCLASS()
class UE4_RCARENA_API AMoneyBox : public ABaseBox
{
	GENERATED_BODY()
	
public:
	AMoneyBox();

	virtual void BreakBox() override;

	int MaxSpawns = 12;
	int MinSpawns = 4;

	TSubclassOf<ABasePickup> PickupToSpawn = nullptr;
};
