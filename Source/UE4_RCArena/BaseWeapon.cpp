// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"
#include "BaseBox.h"
#include "PlayerCharacter.h"
#include "BaseProjectile.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Setup Components
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Body"));
	RootComponent = WeaponMesh;

	AccuracyCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Accuracy Cone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ConeMeshObject(TEXT("/Game/Weapon/Mesh/Cone"));
	if (ConeMeshObject.Succeeded())
	{
		AccuracyCone->SetStaticMesh(ConeMeshObject.Object);
	}

	AccuracyCone->SetupAttachment(WeaponMesh);
	AccuracyCone->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));

	// Change Collision Settings
	WeaponMesh->SetCollisionProfileName(TEXT("NoCollision"));
	AccuracyCone->SetCollisionProfileName(TEXT("Cone"));
	AccuracyCone->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);

	//AccuracyCone->bHiddenInGame = true;

	// Add the BarrelPos
	BarrelPos = CreateDefaultSubobject<USceneComponent>(TEXT("Barrel Position"));
	BarrelPos->SetupAttachment(WeaponMesh);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Set the reference to the PlayerCharacter
	OwningPlayer = Cast<APlayerCharacter>(GetParentActor());

	// Add Cone Collision Functions
	AccuracyCone->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::OnConeBeginOverlap);
	AccuracyCone->OnComponentEndOverlap.AddDynamic(this, &ABaseWeapon::OnConeEndOverlap);	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check if there is more than 0 targets
	if (TargetsArray.Num() > 0)
	{
		// Check if there is exactly one target
		if (TargetsArray.Num() == 1)
		{
			ClosestTarget = TargetsArray[0];
		}
		// Else, check which target is the closest
		else
		{
			int Index;  float CCV;	float NV; // CCV = CurrentClosestTarget / NV = NewTarget
			for (int i = 0; i < TargetsArray.Num(); i++)
			{
				// Check if it is the first cell check (no need to do checks)
				if (i == 0)
				{
					CCV = FVector::Dist(GetActorLocation(), TargetsArray[i]->GetActorLocation());
					Index = i;
				}
				// Else, compare against the CurrentClosestVector
				else
				{
					NV = FVector::Dist(GetActorLocation(), TargetsArray[i]->GetActorLocation());
					// If NV is closer to the player than CCV, make CCV equal NV
					if (CCV > NV)
					{
						CCV = NV;
						Index = i;
					}
					// Else, do nothing...
				}
			}
			// After all checks, set ClosestTarget to the outcome
			ClosestTarget = TargetsArray[Index];
		}
	}
	// Else, make ClosestTarget to nullptr
	else if (TargetsArray.Num() == 0 && ClosestTarget != nullptr)
	{
		ClosestTarget = nullptr;
	}
}

void ABaseWeapon::OnConeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the actor overlapped is either a child of BaseBox or BaseEnemy.  Else, don't add it to the array
	if (OtherActor->GetClass()->IsChildOf(ABaseBox::StaticClass()) == true) // || OtherActor.GetClass() == ABaseEnemy::StaticClass()
	{
		UE_LOG(LogTemp, Warning, TEXT("Added to Array"));
		TargetsArray.Add(OtherActor);
	}
}

void ABaseWeapon::OnConeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Remove the actor from the array
	for (int i = 0; i < TargetsArray.Num(); i++)
	{
		// If the actor that has left the collision is equal to the actor found
		if (TargetsArray[i] == OtherActor)
		{
			// Remove it
			TargetsArray.RemoveAt(i);
		}
	}
}

void ABaseWeapon::FireWeapon()
{
	// Check that the player has ammo to fire this weapon
	if ((OwningPlayer->WeaponInventory[ID].CurrentAmmo - 1) != 0)
	{
		// Remove one from the weapon invent
		OwningPlayer->WeaponInventory[ID].CurrentAmmo--;

		// Fire the weapons corrisponding projectile
		if (BulletToFire != nullptr)
		{
			// Spawn a box at the SpawmPos component
			const FRotator SpawnRot = BarrelPos->GetComponentRotation();
			const FVector SpawnLoc = BarrelPos->GetComponentLocation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			ABaseProjectile* NewBullet = GetWorld()->SpawnActor<ABaseProjectile>(BulletToFire, SpawnLoc, SpawnRot, ActorSpawnParams);
			NewBullet->UpdateProjectileInfo(ClosestTarget);
			UE_LOG(LogTemp, Warning, TEXT("Spawned Bullet"));
		}
	}

}

void ABaseWeapon::SetWeaponStatsFromLevel(int InLevel)
{
	for (int i = 0; i < StatsAtEachLevel.Num(); i++)
	{
		if (StatsAtEachLevel[i].Level == InLevel)
		{
			CurrentStats = StatsAtEachLevel[i];
		}
	}
}


