// Fill out your copyright notice in the Description page of Project Settings.

#include "Devastator.h"
#include "BaseProjectile.h"

ADevastator::ADevastator()
{
	// Set this child classes base variables
	ID = 1;

	StatsAtEachLevel =
	{
		{"Devastator", Base, 1, 30, 200, 20},
	};

	// Find and set the mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh>WeaponMeshObject(TEXT("/Game/Weapon/Mesh/SM_Devastator"));
	if (WeaponMeshObject.Succeeded())
	{
		WeaponMesh->SetStaticMesh(WeaponMeshObject.Object);
	}

	// Find and set the projectile to fire
	//static ConstructorHelpers::FClassFinder<ABaseProjectile>ProjectileClass(TEXT(""));
	//if (WeaponMeshObject.Succeeded())
	//{
		//BulletToFire = ProjectileClass.Class;
	//}

	// Modify the AccuracyCone and BarrelPos
	AccuracyCone->SetRelativeLocation(FVector(0.0f, -7.0f, 450.0f));
	AccuracyCone->SetRelativeScale3D(FVector(6.0f, 4.0f, 8.0f));

	BarrelPos->SetRelativeLocation(FVector(0.0f, -7.0f, 40.0f));

}

void ADevastator::FireWeapon()
{

}
