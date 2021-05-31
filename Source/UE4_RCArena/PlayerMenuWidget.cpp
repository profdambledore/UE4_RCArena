// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMenuWidget.h"

#include "PlayerCharacter.h"
#include "RoundCrtl.h"
#include "Engine/DataTable.h"


void UPlayerMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FScriptDelegate NxtBtnDelagate;
	NxtBtnDelagate.BindUFunction(this, "NextChallenge");
	NextButton->OnReleased.Add(NxtBtnDelagate);

	FScriptDelegate PrevBtnDelagate;
	PrevBtnDelagate.BindUFunction(this, "PrevChallenge");
	PrevButton->OnReleased.Add(PrevBtnDelagate);

	FScriptDelegate SelBtnDelagate;
	SelBtnDelagate.BindUFunction(this, "SelectChallenge");
	SelectButton->OnReleased.Add(SelBtnDelagate);
}

void UPlayerMenuWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

}

void UPlayerMenuWidget::SetupRowNames()
{
	if (ControlRef != nullptr)
	{
		ChallengeRowNames = ControlRef->FChallengeDataTable->GetRowNames();
	}
	UpdateShownChallenge(CurrentSelection);
}

void UPlayerMenuWidget::NextChallenge()
{
	if (CurrentSelection != (ChallengeRowNames.Num() - 1))
	{
		CurrentSelection++;
		UpdateShownChallenge(CurrentSelection);
	}
	else
	{
		CurrentSelection = 0;
		UpdateShownChallenge(CurrentSelection);
	}
}

void UPlayerMenuWidget::PrevChallenge()
{
	if (CurrentSelection == 0)
	{
		CurrentSelection = (ChallengeRowNames.Num() - 1);
		UpdateShownChallenge(CurrentSelection);
	}
	else
	{
		CurrentSelection--;
		UpdateShownChallenge(CurrentSelection);
	}
}

void UPlayerMenuWidget::SelectChallenge()
{
	ControlRef->SetCurrentChallenge(CurrentSelection);
	PlayerRef->ToggleMenu();
}

void UPlayerMenuWidget::UpdateShownChallenge(int InIndex)
{
	FChallenge* ChallengeToDisplay = ControlRef->FChallengeDataTable->FindRow<FChallenge>(ChallengeRowNames[InIndex], FString("Meme"), true);
	NameText->SetText(FText::FromString(ChallengeToDisplay->Name));
	RewardText->SetText(FText::FromString(FString::FromInt(ChallengeToDisplay->MoneyPayout)));
}
