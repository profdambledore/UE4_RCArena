// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "PlayerHUDWidget.generated.h"

class APlayerCharacter;
class ABaseWeapon;

UCLASS()
class UE4_RCARENA_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UFUNCTION()
		//void SetupRoundRef(ARoundCtrl* InRef);

	virtual void SynchronizeProperties() override;

	// Update Functions
	void UpdateHealth();
	void UpdateWeapon();
	void UpdateMoney();
	void UpdateRound();

public:
	// Components
	// Health
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* HealthBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CurrentHealth = nullptr;

	// Weapon
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* WeaponBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* WeaponImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* WeaponAmmo = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* WeaponXP = nullptr;

	// Money
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* MoneyBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* MoneyImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CurrentMoney = nullptr;

	// Round
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* RoundBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* CurrentRound = nullptr;

	// References
	APlayerCharacter* PlayerRef = nullptr;
	class ARoundCrtl* RoundCtrlRef = nullptr;
};
