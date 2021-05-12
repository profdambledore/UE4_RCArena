// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUDWidget.h"

#include "PlayerCharacter.h"
#include "BaseWeapon.h"
//#include "RoundCtrl.h"

void UPlayerHUDWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	// Update all elements
	if (HealthBackground)
	{
		if (PlayerRef)
		{
			UpdateHealth();
			UpdateWeapon();
			UpdateMoney();
			UpdateRound();
		}
	}
}

void UPlayerHUDWidget::UpdateHealth()
{
	// Update the CurrentHealth text
	TArray< FStringFormatArg > Arguments;
	Arguments.Add(FStringFormatArg(PlayerRef->CurrentHealth));
	Arguments.Add(FStringFormatArg(PlayerRef->MaxHealth));

	CurrentHealth->SetText(FText::FromString(FString::Format(TEXT("{0} / {1}"), Arguments)));
}

void UPlayerHUDWidget::UpdateWeapon()
{
	// Update the WeaponImage
	WeaponImage->SetBrushFromTexture(PlayerRef->WeaponInventory[PlayerRef->CurrentWeaponID].Icon);

	// Update the WeaponAmmo text
	TArray< FStringFormatArg > Arguments;
	Arguments.Add(FStringFormatArg(PlayerRef->WeaponInventory[PlayerRef->CurrentWeaponID].CurrentAmmo));
	Arguments.Add(FStringFormatArg(PlayerRef->CurrentWeapon->CurrentStats.MaxAmmo));

	WeaponAmmo->SetText(FText::FromString(FString::Format(TEXT("{0} / {1}"), Arguments)));
}

void UPlayerHUDWidget::UpdateMoney()
{
	// Update the CurrentMoney text
	CurrentMoney->SetText(FText::FromString(FString::FromInt(PlayerRef->Money)));
}

void UPlayerHUDWidget::UpdateRound()
{

}
