// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "StructEnumLibrary.h"

#include "BoxSpawner.generated.h"

class ABaseBox;

UCLASS()
class UE4_RCARENA_API ABoxSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void SpawnBox(TEnumAsByte<EBoxType> BoxToSpawn);

	void SpawnBoxRandom();

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* SpawnPos;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boxes")
		TEnumAsByte<EBoxType> TestBoxSpawn;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boxes")
		TArray<FBoxTypes> BoxTypesArray =
	{
		{Money, nullptr},
		{Ammo, nullptr},
		{Health, nullptr},
	};
};
