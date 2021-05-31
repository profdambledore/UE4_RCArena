// Fill out your copyright notice in the Description page of Project Settings.

#include "RoundCrtl.h"

#include "UObject/ConstructorHelpers.h"
#include "BaseEnemy.h"

// Sets default values
ARoundCrtl::ARoundCrtl()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> FChallengeDTObject(TEXT("/Game/Challenges/DT_Challenges"));
	if (FChallengeDTObject.Succeeded())
	{
		FChallengeDataTable = FChallengeDTObject.Object;
	}

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoundCrtl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoundCrtl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

