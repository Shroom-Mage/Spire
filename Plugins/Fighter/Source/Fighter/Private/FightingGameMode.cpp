// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGameMode.h"
#include "FighterPawn.h"
#include "Kismet/GameplayStatics.h"

AFightingGameMode::AFightingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFightingGameMode::AddPoint(AFighterPawn* Recipient)
{
	int Round = GetRound();

	if (Recipient == Fighter0)
		Score0++;
	else if (Recipient == Fighter1)
		Score1++;

	if (GetRound() > Round) {
		BeginRound();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Score: %i"), GetScore(Recipient)));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Round: %i"), GetRound()));

	BeginPoint();
}

void AFightingGameMode::ResetPositions()
{
	if (Fighter0) {
		Fighter0->SetActorLocation(FVector(StartingPosition0, 0.0, 0.0));
		Fighter0->FaceDirection(true);
	}
	if (Fighter1) {
		Fighter1->SetActorLocation(FVector(StartingPosition1, 0.0, 0.0));
		Fighter1->FaceDirection(false);
	}
}

void AFightingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(GetWorld(), -1);

	Fighter0 = Cast<AFighterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Fighter1 = Cast<AFighterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));

	BeginMatch();
	BeginRound();
	BeginPoint();
}

void AFightingGameMode::BeginMatch()
{
	OnBeginMatch();

	Fighter0->BeginMatch();
	Fighter1->BeginMatch();
}

void AFightingGameMode::BeginRound()
{
	OnBeginRound();

	Fighter0->BeginRound();
	Fighter1->BeginRound();
}

void AFightingGameMode::BeginPoint()
{
	OnBeginPoint();

	ResetPositions();

	Fighter0->BeginPoint();
	Fighter1->BeginPoint();
}

void AFightingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Fighter0 && Fighter1) {
		double Position0 = Fighter0->GetActorLocation().X;
		double Position1 = Fighter1->GetActorLocation().X;

		// Fighter0 is to the left of Fighter1
		if (Position0 < Position1) {
			if (!Fighter0->GetIsFacingRight())
				Fighter0->FaceDirection(true);
			if (Fighter1->GetIsFacingRight())
				Fighter1->FaceDirection(false);
		}
		// Fighter1 is to the left of Fighter0
		if (Position1 < Position0) {
			if (!Fighter1->GetIsFacingRight())
				Fighter1->FaceDirection(true);
			if (Fighter0->GetIsFacingRight())
				Fighter0->FaceDirection(false);
		}
	}
}

int AFightingGameMode::GetScore(AFighterPawn* FightingComp)
{
	if (FightingComp == Fighter0)
		return Score0;
	else if (FightingComp == Fighter1)
		return Score1;

	return 0;
}

int AFightingGameMode::GetRound()
{
	return FMath::Clamp(((Score0 + Score1) / 5) + 1, 0, 3);
}
