// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "Devastator.generated.h"


UCLASS()
class UE4_RCARENA_API ADevastator : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	ADevastator();

	void FireWeapon();


public:
	// Variables
	TArray<FWeaponStats> StatsAtEachLevel =
	{
		{"Devastator", Base, 1, 30, 200, 20},
	};

	FVector AccuracyConeScale = FVector(1.0f, 1.0f, 1.0f);
};
