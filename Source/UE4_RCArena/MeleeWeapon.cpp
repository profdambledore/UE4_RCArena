// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeWeapon.h"

#include "UObject/ConstructorHelpers.h"

#include "PlayerCharacter.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
	// Setup Static Meshes (Body, Scope and RenderPlane)
	MeleeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Melee Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeleeMeshObject(TEXT("/Game/Weapon/Mesh/SM_MeleeWeapon"));
	if (MeleeMeshObject.Succeeded())
	{
		MeleeMesh->SetStaticMesh(MeleeMeshObject.Object);
	}

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

