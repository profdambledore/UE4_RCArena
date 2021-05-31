// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"

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
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		int CurrentAmmo;

	UPROPERTY(EditAnywhere)
		int MaxAmmo;

	UPROPERTY(EditAnywhere)
		int AmmoPerPickup;

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

// Pickups
USTRUCT(BlueprintType)
struct FBoltTypes
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Mesh;
};

// Round Control
USTRUCT(BlueprintType)
struct FAmountOfEnemy : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ABaseEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Amount;
};

USTRUCT(BlueprintType)
struct FAmountOfBox : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TEnumAsByte<EBoxType> Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int Amount;
};

USTRUCT(BlueprintType)
struct FEnemyGroup : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FAmountOfEnemy> AmountOfEnemy;

};

USTRUCT(BlueprintType)
struct FInduvidualRound : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FEnemyGroup> GroupOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FAmountOfBox> BoxSpawns;
};


USTRUCT(BlueprintType)
struct FChallenge : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int MoneyPayout;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FInduvidualRound> InduvidualRound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsUnlocked;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString UnlockAfterCompleting;
};
