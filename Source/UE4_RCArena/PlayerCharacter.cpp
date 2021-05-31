// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"

#include "PlayerHUD.h"
#include "MeleeWeapon.h"
#include "BaseWeapon.h"
#include "BasePickup.h"

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

	// Setup Weapon ChildActorComponent
	WeaponChildComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon Component"));
	WeaponChildComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("WeaponSocket"));

	// Setup the pickup range
	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Range"));
	PickupRange->SetSphereRadius(200.0);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnPickupBeginOverlap);
	PickupRange->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnPickupEndOverlap);
	
	// Get refernce to the player controller
	PC = Cast<APlayerController>(GetController());

	// Get reference to the player HUD
	HUDRef = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	HUDRef->SetPlayerRef(this);

	// Set the players health to their max value
	CurrentHealth = MaxHealth;

	// Show the challenge select menu
	PC->bShowMouseCursor = true; 
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
	//ToggleMenu();

	// Test
	EquipWeapon(WeaponInventory[0].ID);
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
	PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &APlayerCharacter::FireWeapon);
	PlayerInputComponent->BindAction("FireWeapon", IE_Released, this, &APlayerCharacter::StopFiring);
	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &APlayerCharacter::NextWeapon);
	PlayerInputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &APlayerCharacter::PrevWeapon);
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

void APlayerCharacter::OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check to see if the collided pickup is a money pickup
	if (OtherActor->GetClass()->IsChildOf(ABasePickup::StaticClass()) == true)
	{
		CollectPickup(OtherActor);
		GetWorld()->DestroyActor(OtherActor, false, false);
	}
}

void APlayerCharacter::OnPickupEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

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

void APlayerCharacter::FireWeapon()
{
	if (bInMenu == false)
	{
		// Check that there is a weapon equiped
		if (CurrentWeapon != nullptr)
		{
			CurrentWeapon->FireWeapon();
		}
	}
}

void APlayerCharacter::StopFiring()
{

}

void APlayerCharacter::NextWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Next"));
	// Move one weapon up in the CicleMenu array
	// Find the weapons position in the array
	bool bFoundWeapon = false;
	for (int i = 0; i < CircleWheel.Num(); i++)
	{
		if (bFoundWeapon == false)
		{
			if (CurrentWeapon->ID == CircleWheel[i])
			{
				bFoundWeapon = true;
				// Check if it is at the end of the array
				if (i != (CircleWheel.Num() - 1))
				{
					// Get the weapon at the first position in the array
					EquipWeapon(CircleWheel[(i + 1)]);
				}
				else
				{
					// Get the weapon at the next array index
					EquipWeapon(CircleWheel[0]);
				}
			}
		}
	}
}

void APlayerCharacter::PrevWeapon()
{
	UE_LOG(LogTemp, Warning, TEXT("Prev"));
	// Move one weapon down in the CicleMenu array
	// Find the weapons position in the array
	bool bFoundWeapon = false;
	for (int i = 0; i < CircleWheel.Num(); i++)
	{
		if (bFoundWeapon == false)
		{
			if (CurrentWeapon->ID == CircleWheel[i])
			{
				bFoundWeapon = true;
				// Check if it is at the start of the array
				if (i == 0)
				{
					// Get the weapon at the first position in the array
					EquipWeapon(CircleWheel[(CircleWheel.Num() - 1)]);
				}
				else
				{
					// Get the weapon at the previous array index
					EquipWeapon(CircleWheel[(i - 1)]);
				}
			}
		}
	}
}

void APlayerCharacter::ToggleMenu()
{
	if (bInMenu == true)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
		bInMenu = false;
		HUDRef->ShowChallengeMenu(false);
	}
	else
	{
		PC->bShowMouseCursor = true; 
		PC->bEnableClickEvents = true; 
		PC->bEnableMouseOverEvents = true;
		bInMenu = true;
		HUDRef->ShowChallengeMenu(true);
	}
}

bool APlayerCharacter::CheckOwnedWeapon(int InID)
{
	bool Out = false;
	// Go through the array
	for (int i = 0; i < WeaponInventory.Num(); i++)
	{
		// Check the InID to the Inventory
		if (WeaponInventory[i].ID == InID)
		{
			// Check if the weapon trying to equip is owned
			if (WeaponInventory[i].bOwned == true)
			{
				Out = true;
			}
		}
	}
	return Out;
}

void APlayerCharacter::EquipWeapon(int InID)
{
	if (CheckOwnedWeapon(InID) == true)
	{
		WeaponChildComponent->SetChildActorClass(WeaponInventory[InID].WeaponClass);
		CurrentWeapon = Cast<ABaseWeapon>(WeaponChildComponent->GetChildActor());
		CurrentWeaponID = InID;
		if (HUDRef->PlayerHUDWidget != nullptr)
		{
			HUDRef->UpdateHUDElements({ "Weapon" });
		}
	}
}

void APlayerCharacter::UnequipWeapon()
{
	WeaponChildComponent->SetChildActorClass(nullptr);
	CurrentWeapon = nullptr;
}

void APlayerCharacter::TakeDamage(int Amount)
{
	// Check if the player has enough health
	if ((CurrentHealth - Amount) <= 0)
	{
		KillPlayer();
	}
	else
	{
		CurrentHealth = CurrentHealth - Amount;
	}
	HUDRef->UpdateHUDElements({ "Health" });
}

void APlayerCharacter::RestoreHealth()
{
	int NewHealth = CurrentHealth;
	NewHealth += (MaxHealth / 5);
	if (NewHealth > MaxHealth)
	{
		NewHealth = MaxHealth;
	}
	CurrentHealth = NewHealth;
	HUDRef->UpdateHUDElements({ "Health" });
}

void APlayerCharacter::AddMoney(int InAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Added Money"));
	Money = Money + InAmount;
	HUDRef->UpdateHUDElements({ "Money" });
}

void APlayerCharacter::AddAmmo()
{
	UE_LOG(LogTemp, Warning, TEXT("Added Ammo"));
	// Get a list of all weapons less than max ammo
	TArray<int> WeaponsCanAddAmmo;
	for (int i = 0; i < WeaponInventory.Num(); i++)
	{
		if (WeaponInventory[i].CurrentAmmo != WeaponInventory[i].MaxAmmo)
		{
			WeaponsCanAddAmmo.Add(i);
		}
	}

	if (WeaponsCanAddAmmo.Num() > 0)
	{
		// Choose a random weapon that can add ammo
		int IndexToAddAt = FMath::RandRange(0, WeaponsCanAddAmmo.Num() - 1);

		// Add to the selected index if one can add ammo
		int NewAmmo = WeaponInventory[WeaponsCanAddAmmo[IndexToAddAt]].CurrentAmmo;
		NewAmmo += WeaponInventory[WeaponsCanAddAmmo[IndexToAddAt]].AmmoPerPickup;
		if (NewAmmo > WeaponInventory[WeaponsCanAddAmmo[IndexToAddAt]].MaxAmmo)
		{
			NewAmmo = WeaponInventory[WeaponsCanAddAmmo[IndexToAddAt]].MaxAmmo;
		}
		WeaponInventory[WeaponsCanAddAmmo[IndexToAddAt]].CurrentAmmo = NewAmmo;
	}
	HUDRef->UpdateHUDElements({ "Weapon" });
}

void APlayerCharacter::KillPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("You have died"))
}