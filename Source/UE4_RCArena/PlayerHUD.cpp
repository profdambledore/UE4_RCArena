// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"

#include "PlayerCharacter.h"
#include "PlayerHUDWidget.h"
#include "PlayerMenuWidget.h"
#include "RoundCrtl.h"

class PlayerHUD;

APlayerHUD::APlayerHUD()
{
	// Setup Widget Components
	static ConstructorHelpers::FClassFinder<UPlayerHUDWidget>FoundPHWidget(TEXT("/Game/Player/Blueprint/WBP_PlayerHUD"));
	if (FoundPHWidget.Succeeded())
	{
		PlayerHUDWidgetComponent = FoundPHWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UPlayerMenuWidget>FoundPMWidget(TEXT("/Game/Player/Blueprint/WBP_ChallengeSelect"));
	if (FoundPMWidget.Succeeded())
	{
		PlayerMenuWidgetComponent = FoundPMWidget.Class;
	}
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	// Find the Player
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		PlayerRef = Cast<APlayerCharacter>(FoundActors[0]);
	}

	// Find the RoundCrtl object in the world and set a reference
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARoundCrtl::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		RoundRef = Cast<ARoundCrtl>(FoundActors[0]);
	}

	// Add the PlayerHUDWidget to the HUD
	if (PlayerHUDWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("HUD class was found"));
		PlayerHUDWidget = CreateWidget<UPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetComponent);

		// Check that it was created
		if (PlayerHUDWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));
			// Add to viewport
			PlayerHUDWidget->AddToViewport();
			PlayerHUDWidget->PlayerRef = PlayerRef;
			PlayerHUDWidget->RoundCtrlRef = RoundRef;
		}
	}

	// Add the PlayerHUDWidget to the HUD
	if (PlayerMenuWidgetComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Menu class was found"));
		PlayerMenuWidget = CreateWidget<UPlayerMenuWidget>(GetWorld(), PlayerMenuWidgetComponent);

		// Check that it was created
		if (PlayerMenuWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Added to viewport"));
			// Add to viewport
			PlayerMenuWidget->AddToViewport();
			PlayerMenuWidget->PlayerRef = PlayerRef;
			PlayerMenuWidget->ControlRef = RoundRef;
			PlayerMenuWidget->SetupRowNames();
		}
	}
}

// Setup references to charatcer classes (character and weapon)
void APlayerHUD::SetPlayerRef(APlayerCharacter* InRef)
{
	//PlayerRef = InRef;
}

// Update all HUD Widgets
void APlayerHUD::UpdateHUDElements(TArray<FString> InArgs)
{
	for (int i = 0; i < InArgs.Num(); i++)
	{
		if (InArgs[i] == "Health")
		{
			PlayerHUDWidget->UpdateHealth();
		}
		else if (InArgs[i] =="Weapon")
		{
			PlayerHUDWidget->UpdateWeapon();
		}
		else if (InArgs[i] == "Money")
		{
			PlayerHUDWidget->UpdateMoney();
		}
		else if (InArgs[i] == "Rounds")
		{
			PlayerHUDWidget->UpdateRound();
		}
	}
}

void APlayerHUD::ShowChallengeMenu(bool bShow)
{
	if (bShow == true)
	{
		PlayerMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerHUDWidget->SynchronizeProperties();
	}
}

void APlayerHUD::DrawHUD()
{

}

void APlayerHUD::Tick(float DeltaSeconds)
{

}