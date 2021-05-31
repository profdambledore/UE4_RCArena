// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

#include "StructEnumLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"

#include "PlayerCharacter.generated.h"

class ABasePickup;

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

	UFUNCTION(BlueprintCallable)
		void ToggleMenu();

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
	void NextWeapon();
	void PrevWeapon();

	// Weapon Functions
	bool CheckOwnedWeapon(int InID);
	void EquipWeapon(int InID);
	void UnequipWeapon();

	// Damage Functions
	UFUNCTION(BlueprintCallable)
		void TakeDamage(int Amount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetInvunrabilityTime(float Time, int Amount);

	UFUNCTION(BlueprintCallable)
		void RestoreHealth();

	UFUNCTION(BlueprintCallable)
		void AddMoney(int InAmount);

	UFUNCTION(BlueprintCallable)
		void AddAmmo();

	UFUNCTION(BlueprintCallable)
		void KillPlayer();

	// Overlap Functions
	UFUNCTION()
		void OnPickupBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPickupEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void CollectPickup(AActor* InOtherActor);

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* ThirdPersonSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* MeleeWeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UChildActorComponent* WeaponChildComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USphereComponent* PickupRange;

	// Variables
	// References
	APlayerController* PC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class APlayerHUD* HUDRef;

	class AMeleeWeapon* MeleeWeapon;
	class ABaseWeapon* CurrentWeapon;

	// States
	bool bInMenu = true;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int TimesTouchedLava = 0;

	// Weapons
	int CurrentWeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<FPlayerWeaponInventory> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TArray<int> CircleWheel = {
			{0},
			{1},
	};

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool bIsInvunrable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		int MaxHealth = 20;

	// Money
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Money")
		int Money;

};
