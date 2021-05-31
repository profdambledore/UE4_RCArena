// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxSpawner.h"

#include "BaseBox.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
	// Setup Mesh
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SpawnerMeshObject(TEXT("/Game/Box/Mesh/SM_BoxSpawner"));
	if (SpawnerMeshObject.Succeeded())
	{
		SpawnerMesh->SetStaticMesh(SpawnerMeshObject.Object);
	}

	// Setup SpawnPos
	SpawnPos = CreateDefaultSubobject<USceneComponent>(TEXT("Box Spawn Location"));
	SpawnPos->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));

	// Find all box classes and set them in the array
	static ConstructorHelpers::FClassFinder<ABaseBox>MoneyBoxClass(TEXT("/Script/UE4_RCArena.MoneyBox"));
	if (MoneyBoxClass.Succeeded())
	{
		BoxTypesArray[0].BoxClass = MoneyBoxClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ABaseBox>AmmoBoxClass(TEXT("/Script/UE4_RCArena.AmmoBox"));
	if (AmmoBoxClass.Succeeded())
	{
		BoxTypesArray[1].BoxClass = AmmoBoxClass.Class;
	}

	static ConstructorHelpers::FClassFinder<ABaseBox>HealthBoxClass(TEXT("/Script/UE4_RCArena.HealthBox"));
	if (HealthBoxClass.Succeeded())
	{
		BoxTypesArray[2].BoxClass = HealthBoxClass.Class;
	}
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ABoxSpawner::SpawnBox(TEnumAsByte<EBoxType> BoxToSpawn)
{
	// Get the class to spawn from the array
	TSubclassOf<ABaseBox> BoxClass = nullptr;
	for (int i = 0; i < BoxTypesArray.Num(); i++)
	{
		if (BoxTypesArray[i].Type == BoxToSpawn)
		{
			BoxClass = BoxTypesArray[i].BoxClass;
		}
	}

	// Check to see if a class was found
	if (BoxClass != nullptr)
	{
		// Spawn a box at the SpawmPos component
		const FRotator SpawnRot = SpawnPos->GetComponentRotation();
		const FVector SpawnLoc = SpawnPos->GetComponentLocation();
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor<ABaseBox>(BoxClass, SpawnLoc, SpawnRot, ActorSpawnParams);
	}
}

void ABoxSpawner::SpawnBoxRandom()
{

}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

