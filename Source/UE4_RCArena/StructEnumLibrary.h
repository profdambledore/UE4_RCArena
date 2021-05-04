// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"

#include "StructEnumLibrary.generated.h"

UCLASS()
class UE4_RCARENA_API UStructEnumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};

UENUM()
enum EWeaponVersion
{
	Base UMETA(Display Name = "Base"),
	Upgrade UMETA(Display Name = "Upgrade"),
	Mega UMETA(Display Name = "Mega"),
	Ultra UMETA(Display Name = "Ultra"),
};

USTRUCT(BlueprintType)
struct FWeapons : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		class ABaseWeapon* Class;
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EWeaponVersion> Version;

	UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		int Damage;

	UPROPERTY(EditAnywhere)
		int MaxAmmo;

	UPROPERTY(EditAnywhere)
		int AmmoPerPickup;
};

USTRUCT(BlueprintType)
struct FPlayerWeaponInventory
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		int ID;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		int CurrentAmmo;

	UPROPERTY(EditAnywhere)
		bool bOwned;
};