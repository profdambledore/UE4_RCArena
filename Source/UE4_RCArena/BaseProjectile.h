// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

#include "BaseProjectile.generated.h"

class ABaseBox;
class ABaseEnemy;

UCLASS()
class UE4_RCARENA_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to update the projectile.  Used to set if tracking a target and what target
	void UpdateProjectileInfo(AActor* TrackingTarget);

	// Overlap Functions
	UFUNCTION()
		void OnProjBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnProjEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USphereComponent* ProjectileCollsion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent* ProjectileParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UProjectileMovementComponent* ProjectileMovement;
};
