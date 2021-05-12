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
};
