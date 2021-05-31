// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

#include "StructEnumLibrary.h"
#include "Math/Vector.h"

#include "BaseWeapon.generated.h"

class ABaseBox;
class ABaseEnemy;
class ABaseProjectile;
class UWeaponTargetWidget;

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

	// Overlap Functions
	UFUNCTION()
		void OnConeBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnConeEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* AccuracyCone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* BarrelPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* TargetWidget;

	// Variables
	// References
	class APlayerCharacter* OwningPlayer;
	TSubclassOf<class ABaseProjectile> BulletToFire = nullptr;

	// Targeting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targets")
		TArray<AActor*> TargetsArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Targets")
		AActor* ClosestTarget;

	UPROPERTY()
		FWeaponStats CurrentStats;

	UPROPERTY()
		int CurrentXP;

	UPROPERTY()
		TArray<FWeaponStats> StatsAtEachLevel;

	int ID;
};
