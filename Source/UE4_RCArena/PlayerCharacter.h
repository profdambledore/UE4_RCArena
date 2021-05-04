// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/ArrowComponent.h"

#include "StructEnumLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class UE4_RCARENA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Inputs
	// Axis
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void RotateCameraX(float AxisValue);
	void RotateCameraY(float AxisValue);
	// void NextWeapon(float AxisValue);

	// Action
	void Crouch();
	void Strafe();
	// void MeleeAttack();
	void FireWeapon();
	void StopFiring();
	// void CircleMenu();

	bool CheckOwnedWeapon(int InID);
	void EquipWeapon(int InID);
	void UnequipWeapon();

	void TakeDamage(int Amount);
	void RestoreHealth();

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* MeleeWeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* WeaponChildComponent;

	// Variables
	// References
	APlayerController* PC;
	class APlayerHUD* HUDRef;
	class AMeleeWeapon* MeleeWeapon;
	class ABaseWeapon* CurrentWeapon;

	// States
	bool bInMenu = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bInAir = false;

	bool bIsCrouched = false;
	bool bIsStrafe = false;
	bool bHasMelee = false;

	// Jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int CurrJumps = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		int MaxJumps = 2;

	// Weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<FPlayerWeaponInventory> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<int> CircleWheel;

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int MaxHealth = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int HealPerPickup = 20;

};
