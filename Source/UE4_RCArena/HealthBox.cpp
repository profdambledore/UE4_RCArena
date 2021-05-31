// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBox.h"
#include "BasePickup.h"

AHealthBox::AHealthBox()
{
	// Set the mesh of the box
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BoxMeshObject(TEXT("/Game/Box/Mesh/SM_HealthBox"));
	if (BoxMeshObject.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshObject.Object);
	}

	// Find the money class and store it for later
	static ConstructorHelpers::FClassFinder<ABasePickup>PickupClass(TEXT("/Game/Pickup/Blueprint/BP_HealthPickup"));
	if (PickupClass.Succeeded())
	{
		PickupToSpawn = PickupClass.Class;
	}
}

void AHealthBox::BreakBox()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Spawn a random number in a range of money pickups
	int AmountToSpawn = FMath::RandRange(MinSpawns, MaxSpawns);
	for (int i = 0; i < AmountToSpawn; i++)
	{
		// Get a random vector in range
		const FRotator SpawnRot = BoxMesh->GetComponentRotation();

		FVector BML = BoxMesh->GetComponentLocation();
		float SLX = FMath::RandRange(BML.X - 50, BML.X + 50);
		float SLY = FMath::RandRange(BML.Y - 50, BML.Y + 50);
		float SLZ = BML.Z + 40;
		const FVector SpawnLoc = FVector(SLX, SLY, SLZ);

		GetWorld()->SpawnActor<ABasePickup>(PickupToSpawn, SpawnLoc, SpawnRot, ActorSpawnParams);
	}

}