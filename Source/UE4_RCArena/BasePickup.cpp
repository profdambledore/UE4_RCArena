// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"
#include "PlayerCharacter.h"

// Sets default values
ABasePickup::ABasePickup()
{
	// Setup Components
	// Sphere
	PickupRoot = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Sphere"));
	RootComponent = PickupRoot;

	// Mesh
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	PickupMesh->SetupAttachment(PickupRoot);

	PickupRoot->SetSimulatePhysics(true);
	PickupRoot->SetCollisionProfileName(TEXT("Pickup"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

