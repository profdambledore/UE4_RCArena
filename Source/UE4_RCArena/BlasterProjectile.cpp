// Fill out your copyright notice in the Description page of Project Settings.

#include "BlasterProjectile.h"

ABlasterProjectile::ABlasterProjectile()
{
	// Set the particle system
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ProjectileParticleObject(TEXT("/Game/Weapon/Particle/PS_Blaster"));
	if (ProjectileParticleObject.Succeeded())
	{
		ProjectileParticle->SetTemplate(ProjectileParticleObject.Object);
	}

	// Set the base variables for the projectile movement component
	ProjectileMovement->Velocity = FVector(0.0f, 0.0f, 1.0f);
	ProjectileMovement->ProjectileGravityScale = 0;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->InitialSpeed = 2000.0f;
}