// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "PlayerHUD.h"
#include "MeleeWeapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Add Components
	// Player Mesh
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Find the Ratchet Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>PlayerMeshObject(TEXT("/Game/Player/Mesh/RatchetRigged2"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}

	// Third Person Camera
	ThirdPersonSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Third Person Spring Arm"));
	ThirdPersonSpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	ThirdPersonSpringArm->TargetArmLength = 400.0f;

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonSpringArm, USpringArmComponent::SocketName);

	// Setup Melee Weapon ChildActorComponent
	MeleeWeaponComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Melee Weapon"));
	// Use ConstructorHelpers to find the PlayerWeaponClass
	static ConstructorHelpers::FClassFinder<AActor> MeleeWeaponObject(TEXT("/Game/Weapon/Blueprint/BP_MeleeWeapon"));
	if (MeleeWeaponObject.Succeeded())
	{
		MeleeWeaponComponent ->SetChildActorClass(MeleeWeaponObject.Class);
	}
	// Attach the MeleeWeapon to the MeleeHoldSocket
	MeleeWeaponComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("MeleeHoldSocket"));

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Get refernce to the player controller
	PC = Cast<APlayerController>(GetController());

	// Set the reference to the PlayerWeapon class in the ChildActorComponent
	MeleeWeapon = Cast<AMeleeWeapon>(MeleeWeaponComponent->GetChildActor());

	// Get reference to the player HUD
	HUDRef = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If strafing, rotate to match to the camera rotation
	if (bIsStrafe == true)
	{
		FRotator CtrlRot = GetControlRotation();
		CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
		SetActorRotation(CtrlRot);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Axis Binds
	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveX);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveY);
	PlayerInputComponent->BindAxis("RotateCameraX", this, &APlayerCharacter::RotateCameraX);
	PlayerInputComponent->BindAxis("RotateCameraY", this, &APlayerCharacter::RotateCameraY);

	// Add Action Binds
	PlayerInputComponent->BindAction("Strafe", IE_Pressed, this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAction("Strafe", IE_Released, this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::Crouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::Crouch);
}

void APlayerCharacter::MoveX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bInMenu == false)
		{
			// Move on the X axis based on the controller's yaw value
			FRotator CtrlRot = GetControlRotation();
			CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
			AddMovementInput(UKismetMathLibrary::GetForwardVector(CtrlRot), AxisValue, false);
		}
	}
}

void APlayerCharacter::MoveY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bInMenu == false)
		{
			// Move on the Y axis based on the controller's yaw value
			FRotator CtrlRot = GetControlRotation();
			CtrlRot.Pitch = 0.0f; CtrlRot.Roll = 0.0f;
			AddMovementInput(UKismetMathLibrary::GetRightVector(CtrlRot), AxisValue, false);
		}
	}
}

void APlayerCharacter::RotateCameraX(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bInMenu == false)
		{
			// Rotate on the X axis based on the input's axis value
			AddControllerYawInput(AxisValue);
		}
	}
}

void APlayerCharacter::RotateCameraY(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		if (bInMenu == false)
		{
			// Rotate on the Y axis based on the input's axis value
			AddControllerPitchInput(AxisValue);
		}
	}
}

void APlayerCharacter::Crouch()
{
	if (bIsCrouched == true)
	{
		bIsCrouched = false;
	}
	else if (bIsCrouched == false)
	{
		bIsCrouched = true;
	}
}

void APlayerCharacter::Strafe()
{
	if (bIsStrafe == true)
	{
		bIsStrafe = false;
	}
	else if (bIsStrafe == false)
	{
		bIsStrafe = true;
	}
}