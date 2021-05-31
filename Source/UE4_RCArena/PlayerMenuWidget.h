// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "StructEnumLibrary.h"

#include "PlayerMenuWidget.generated.h"



UCLASS()
class UE4_RCARENA_API UPlayerMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void SynchronizeProperties() override;

	void SetupRowNames();

	UFUNCTION()
		void NextChallenge();

	UFUNCTION()
		void PrevChallenge();

	UFUNCTION()
		void SelectChallenge();

	void UpdateShownChallenge(int InIndex);

public:
	// Components
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* Background = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* NameBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* NameText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* RewardBackground = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* RewardText = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* NextButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* PrevButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UButton* SelectButton = nullptr;

	// Properties
	class APlayerCharacter* PlayerRef = nullptr;
	class ARoundCrtl* ControlRef = nullptr;

	int CurrentSelection = 0;
	TArray<FName> ChallengeRowNames;
};
