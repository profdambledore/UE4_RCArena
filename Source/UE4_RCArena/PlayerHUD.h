// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

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

	UFUNCTION(BlueprintCallable)
		void ShowChallengeMenu(bool bShow);

	// Set the reference to the player
	UFUNCTION()
		void SetPlayerRef(APlayerCharacter* InRef);

protected:

public:
	// Components
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSubclassOf<UUserWidget> PlayerHUDWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		TSubclassOf<UUserWidget> PlayerMenuWidgetComponent;

	// Widgets
	class UPlayerHUDWidget* PlayerHUDWidget;
	class UPlayerMenuWidget* PlayerMenuWidget;

private:
	// Classes
	class APlayerCharacter* PlayerRef = nullptr;
	class ARoundCrtl* RoundRef = nullptr;
};
