// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_RCArenaGameModeBase.h"

#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"

// Constructor function
AUE4_RCArenaGameModeBase::AUE4_RCArenaGameModeBase() : Super()
{
	// Set Base Classes	
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnObject(TEXT("/Game/Player/Blueprint/BP_PlayerCharacter"));
	if (DefaultPawnObject.Succeeded())
	{
		DefaultPawnClass = DefaultPawnObject.Class;
	}

	// Default HUD
	HUDClass = APlayerHUD::StaticClass();
}