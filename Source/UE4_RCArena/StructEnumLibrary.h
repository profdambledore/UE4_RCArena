// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"

#include "StructEnumLibrary.generated.h"

class ABaseBox;
class ABaseEnemy;

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

UENUM()
enum EBoxType
{
	Money UMETA(Display Name = "Money"),
	Ammo UMETA(Display Name = "Ammo"),
	Health UMETA(Display Name = "Health"),
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

USTRUCT(BlueprintType)
struct FBoxTypes
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EBoxType> Type;

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseBox> BoxClass;
};

// Round Control
USTRUCT(BlueprintType)
struct FAmountOfEnemy : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABaseEnemy> EnemyClass;

	UPROPERTY(EditAnywhere)
		int Amount;
};

USTRUCT(BlueprintType)
struct FEnemyGroup : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		TArray<FAmountOfEnemy> AmountOfEnemy;

};

USTRUCT(BlueprintType)
struct FInduvidualRound : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		TArray<FEnemyGroup> GroupOfEnemies;
};


USTRUCT(BlueprintType)
struct FChallenge : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere)
		FString Name;

	UPROPERTY(EditAnywhere)
		int MoneyPayout;

	UPROPERTY(EditAnywhere)
		TArray<FInduvidualRound> InduvidualRound;

	UPROPERTY(EditAnywhere)
		bool bIsUnlocked;

	UPROPERTY(EditAnywhere)
		FString UnlockAfterCompleting;
};
