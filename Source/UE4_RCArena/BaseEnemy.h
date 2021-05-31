// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "BaseEnemy.generated.h"

class ABasePickup;
class ARoundCrtl;

UCLASS()
class UE4_RCARENA_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void DamageEnemy(int InDamage);

	UFUNCTION(BlueprintCallable)
		void KillEneny();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentHealth = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxMoneySpawns = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MinMoneySpawms = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InvunTime;

	TSubclassOf<ABasePickup> MoneyPickup = nullptr;
};
