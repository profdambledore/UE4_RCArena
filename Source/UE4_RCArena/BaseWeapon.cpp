// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeapon.h"

#include "UObject/ConstructorHelpers.h"

#include "PlayerCharacter.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Setup Components
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Body"));

	AccuracyCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Accuracy Cone"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>ConeMeshObject(TEXT("/Game/Weapon/Mesh/Cone"));
	if (ConeMeshObject.Succeeded())
	{
		AccuracyCone->SetStaticMesh(ConeMeshObject.Object);
	}

	// Modify the AccuracyCone to the weapon stats
	AccuracyCone->SetWorldScale3D(AccuracyConeScale);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Set the reference to the PlayerWeapon class in the ChildActorComponent
	OwningPlayer = Cast<APlayerCharacter>(GetParentActor());
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::FireWeapon()
{
	// Remove one from the weapon invent
	OwningPlayer->WeaponInventory[ID].CurrentAmmo--;
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

