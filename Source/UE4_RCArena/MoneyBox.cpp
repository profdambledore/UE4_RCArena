
#include "MoneyBox.h"
#include "BasePickup.h"

AMoneyBox::AMoneyBox()
{
	// Set the mesh of the box
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BoxMeshObject(TEXT("/Game/Box/Mesh/SM_MoneyBox"));
	if (BoxMeshObject.Succeeded())
	{
		BoxMesh->SetStaticMesh(BoxMeshObject.Object);
	}

	// Find the money class and store it for later
	static ConstructorHelpers::FClassFinder<ABasePickup>PickupClass(TEXT("/Game/Pickup/Blueprint/BP_MoneyPickup"));
	if (PickupClass.Succeeded())
	{
		PickupToSpawn = PickupClass.Class;
	}
}

void AMoneyBox::BreakBox()
{
	//Super::BreakBox();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

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
