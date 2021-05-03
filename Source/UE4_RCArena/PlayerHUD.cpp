// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"

#include "PlayerCharacter.h"
#include "PlayerHUDWidget.h"

APlayerHUD::APlayerHUD()
{

}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

}

// Setup references to charatcer classes (character and weapon)
void APlayerHUD::SetPlayerRef(APlayerCharacter* InRef)
{
	PlayerRef = InRef;
}

// Update all HUD Widgets
void APlayerHUD::UpdateHUDElements()
{

}

void APlayerHUD::DrawHUD()
{

}

void APlayerHUD::Tick(float DeltaSeconds)
{

}