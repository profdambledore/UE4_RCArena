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
	// void FireWeapon();
	// void CircleMenu();

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

	// Variables
	APlayerController* PC;
	class APlayerHUD* HUDRef;
	class AMeleeWeapon* MeleeWeapon;

	bool bInMenu = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int CurrJumps = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		int MaxJumps = 2;

	bool bIsCrouched = false;
	bool bIsStrafe = false;
	bool bHasMelee = false;

};
