// Fill out your copyright notice in the Description page of Project Settings.

#include "Devastator.h"

ADevastator::ADevastator()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>WeaponMeshObject(TEXT("/Game/Weapon/Mesh/SM_Devastator"));
	if (WeaponMeshObject.Succeeded())
	{
		WeaponMesh->SetStaticMesh(WeaponMeshObject.Object);
	}

}

void ADevastator::FireWeapon()
{

}
