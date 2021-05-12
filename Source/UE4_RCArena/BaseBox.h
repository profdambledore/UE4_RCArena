// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"

#include "StructEnumLibrary.h"

#include "BaseBox.generated.h"

UCLASS()
class UE4_RCARENA_API ABaseBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBox();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		virtual void BreakBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BoxMesh;

	// Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Box Type")
		TEnumAsByte<EBoxType> BoxType;
};
