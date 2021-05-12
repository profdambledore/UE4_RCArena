// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "UObject/ConstructorHelpers.h"

#include "PlayerHUD.generated.h"


UCLASS()
class UE4_RCARENA_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	APlayerHUD();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Update all HUD elements
	UFUNCTION(BlueprintCallable)
		void UpdateHUDElements(TArray<FString> InArgs);

	// Set the reference to the player
	UFUNCTION()
		void SetPlayerRef(APlayerCharacter* InRef);

protected:

public:
	// Components
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSubclassOf<UUserWidget> PlayerHUDWidgetComponent;

	// Widgets
	class UPlayerHUDWidget* PlayerHUDWidget;

private:
	// Classes
	class APlayerCharacter* PlayerRef = nullptr;
	//class ARoundCtrl* RoundRef = nullptr;
};
