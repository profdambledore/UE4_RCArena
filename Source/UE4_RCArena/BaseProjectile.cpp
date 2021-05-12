// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"

#include "UObject/ConstructorHelpers.h"
#include "BaseBox.h"
#include "BaseEnemy.h"
#include "Engine/World.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Setup Components
	ProjectileCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Collsion"));
	RootComponent = ProjectileCollsion;
	ProjectileCollsion->SetCollisionProfileName(TEXT("Projectile"));

	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Particle System"));
	ProjectileParticle->SetupAttachment(ProjectileCollsion);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileCollsion->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnProjBeginOverlap);
	ProjectileCollsion->OnComponentEndOverlap.AddDynamic(this, &ABaseProjectile::OnProjEndOverlap);
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::UpdateProjectileInfo(AActor* TrackingTarget)
{
	// Check if the projectile has a target to track
	if (TrackingTarget != nullptr)
	{
		// Set it as a tracking projectile
		ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 0.0f);
		ProjectileMovement->bIsHomingProjectile = true;
		ProjectileMovement->HomingAccelerationMagnitude = ProjectileMovement->MaxSpeed;

		// Set what it is tracking
		ProjectileMovement->HomingTargetComponent = TrackingTarget->GetRootComponent();
	}
}

void ABaseProjectile::OnProjBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	// Check if the actor overlapped is either a child of BaseBox or BaseEnemy. 
	if (OtherActor->GetClass()->IsChildOf(ABaseBox::StaticClass()) == true) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Box"));
		// Stop tracking the box, if currently
		if (ProjectileMovement->bIsHomingProjectile == true)
		{
			ProjectileMovement->bIsHomingProjectile = false;
			ProjectileMovement->HomingTargetComponent = nullptr;
		}
		// Cast to BaseBox, and call BreakBox()
		ABaseBox* HitBox = Cast<ABaseBox>(OtherActor->GetClass());
		HitBox->BreakBox();
		GetWorld()->DestroyActor(OtherActor, false, false); // Works.  For some reason, calling Destroy() in BaseBox->BreakBox() caused the program to crash - IsPendingKillPending, where 'this' was null.
	}
	//else if (OtherActor.GetClass()->IsChildOf(ABaseEnemy::StaticClass() == true)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Hit Enemy"));
	//}

	// Destroy the actor, whatever it hits
	Destroy();
}

void ABaseProjectile::OnProjEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

