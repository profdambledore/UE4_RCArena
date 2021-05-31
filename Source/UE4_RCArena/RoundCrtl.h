// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "StructEnumLibrary.h"
#include "Engine/DataTable.h"

#include "RoundCrtl.generated.h"

UCLASS()
class UE4_RCARENA_API ARoundCrtl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoundCrtl();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetCurrentChallenge(int InChallengeIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void RemoveEnemyFromArray(class ABaseEnemy* InEnemy);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Variables
	// Challenge data table
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UDataTable* FChallengeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentRound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FChallenge CurrentChallenge;
};
