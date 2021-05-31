// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"
#include "BasePickup.h"
#include "RoundCrtl.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Add Components
	// Player Mesh
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Find the Ratchet Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>PlayerMeshObject(TEXT("/Game/Player/Mesh/SK_Mannequin"));
	if (PlayerMeshObject.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PlayerMeshObject.Object);
	}

	// Find the money class and store it for later
	static ConstructorHelpers::FClassFinder<ABasePickup>PickupClass(TEXT("/Game/Pickup/Blueprint/BP_MoneyPickup"));
	if (PickupClass.Succeeded())
	{
		MoneyPickup = PickupClass.Class;
	}

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::DamageEnemy(int InDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("Damaged"));
	CurrentHealth = CurrentHealth - InDamage;
	if (CurrentHealth <= 0)
	{
		KillEneny();
	}
}

void ABaseEnemy::KillEneny()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	int MoneySpawnAmount = FMath::RandRange(MinMoneySpawms, MaxMoneySpawns);
	for (int i = 0; i < MoneySpawnAmount; i++)
	{
		// Get a random vector in range
		const FRotator SpawnRot = GetMesh()->GetComponentRotation();

		FVector BML = GetMesh()->GetComponentLocation();
		float SLX = FMath::RandRange(BML.X - 50, BML.X + 50);
		float SLY = FMath::RandRange(BML.Y - 50, BML.Y + 50);
		float SLZ = BML.Z + 40;
		const FVector SpawnLoc = FVector(SLX, SLY, SLZ);

		GetWorld()->SpawnActor<ABasePickup>(MoneyPickup, SpawnLoc, SpawnRot, ActorSpawnParams);
	}

	// Get the round control
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoundCrtl::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		ARoundCrtl* RoundCrtlActor = Cast<ARoundCrtl>(FoundActors[0]);
		RoundCrtlActor->RemoveEnemyFromArray(this);
	}

	// Destroy the enemy
	GetWorld()->DestroyActor(this, false, false);
}

