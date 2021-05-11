// Fill out your copyright notice in the Description page of Project Settings.

#include "Blaster.h"
#include "BaseProjectile.h"

ABlaster::ABlaster()
{
	// Set base variables
	ID = 0;

	StatsAtEachLevel =
	{
		{"Blaster", Base, 1, 30, 200, 20},
	};

	// Set the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>WeaponMeshObject(TEXT("/Game/Weapon/Mesh/SM_Blaster"));
	if (WeaponMeshObject.Succeeded())
	{
		WeaponMesh->SetStaticMesh(WeaponMeshObject.Object);
	}

	// Find and set the projectile to fire
	static ConstructorHelpers::FClassFinder<ABaseProjectile>ProjectileClass(TEXT("/Script/UE4_RCArena.BlasterProjectile"));
	if (ProjectileClass.Succeeded())
	{
		BulletToFire = ProjectileClass.Class;
		UE_LOG(LogTemp, Warning, TEXT("Found Class"));
	}

	// Modify the AccuracyCone and BarrelPos
	AccuracyCone->SetRelativeLocation(FVector(1.0f, -7.0f, 225.0f));
	AccuracyCone->SetRelativeScale3D(FVector(5.0f, 2.0f, 4.0f));

	BarrelPos->SetRelativeLocation(FVector(0.0f, -7.0f, 40.0f));
}

void ABlaster::FireWeapon()
{

}

