// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "StructEnumLibrary.h"

#include "BaseWeapon.generated.h"

UCLASS()
class UE4_RCARENA_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void FireWeapon();

	UFUNCTION()
		void SetWeaponStatsFromLevel(int InLevel);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* AccuracyCone;

	// Variables
	UPROPERTY()
		FWeaponStats CurrentStats;

	UPROPERTY()
		int CurrentXP;

	UPROPERTY()
		TArray<FWeaponStats> StatsAtEachLevel;

	FVector AccuracyConeScale;
	int ID;

	class APlayerCharacter* OwningPlayer;
};
