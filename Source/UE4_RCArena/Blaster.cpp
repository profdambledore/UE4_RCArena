// Fill out your copyright notice in the Description page of Project Settings.

#include "Blaster.h"

ABlaster::ABlaster()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>WeaponMeshObject(TEXT("/Game/Weapon/Mesh/SM_Blaster"));
	if (WeaponMeshObject.Succeeded())
	{
		WeaponMesh->SetStaticMesh(WeaponMeshObject.Object);
	}

}

void ABlaster::FireWeapon()
{

}

