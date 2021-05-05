// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"

#include "Blaster.generated.h"

UCLASS()
class UE4_RCARENA_API ABlaster : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	ABlaster();

	void FireWeapon();


public:
	// Variables
	TArray<FWeaponStats> StatsAtEachLevel =
	{
		{"Blaster", Base, 1, 30, 200, 20},
	};

	FVector AccuracyConeScale = FVector(4.0f, 4.0f, 4.0f);
};
