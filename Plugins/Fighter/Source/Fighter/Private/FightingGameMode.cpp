// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGameMode.h"
#include "FighterPawn.h"
#include "Kismet/GameplayStatics.h"

AFightingGameMode::AFightingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	Fighters = { nullptr, nullptr };
	Score = { 0, 0 };
	StartingPositions = { -200.0, 200.0 };
}

void AFightingGameMode::RegisterHit(AFighterPawn* Attacker, AFighterPawn* Recipient)
{
	int Round = GetRound();

	if (Attacker->Owner == Recipient || Recipient->Owner == Attacker)
		return;

	if (Recipient == Fighters[0])
		Score[1]++;
	else if (Recipient == Fighters[1])
		Score[0]++;
	else
		return;

	if (GetRound() > Round) {
		BeginRound();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Score: %i"), GetScore(Attacker)));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Round: %i"), GetRound()));

	BeginPoint();
}

void AFightingGameMode::ResetPositions()
{
	if (Fighters[0]) {
		Fighters[0]->SetActorLocation(FVector(StartingPositions[0], 0.0, 0.0));
		Fighters[0]->FaceDirection(true);
	}
	if (Fighters[1]) {
		Fighters[1]->SetActorLocation(FVector(StartingPositions[1], 0.0, 0.0));
		Fighters[1]->FaceDirection(false);
	}
}

void AFightingGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::CreatePlayer(GetWorld(), -1);

	Fighters[0] = Cast<AFighterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Fighters[1] = Cast<AFighterPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 1));

	Fighter0->GetSkeletalMeshComponent()->SetMaterial(0, Fighter0Material);
	Fighter0->GetSkeletalMeshComponent()->SetMaterial(1, Fighter0Material);
	Fighter1->GetSkeletalMeshComponent()->SetMaterial(0, Fighter1Material);
	Fighter1->GetSkeletalMeshComponent()->SetMaterial(1, Fighter1Material);

	BeginMatch();
	BeginRound();
	BeginPoint();
}

void AFightingGameMode::BeginMatch()
{
	OnBeginMatch();

	Fighters[0]->BeginMatch();
	Fighters[1]->BeginMatch();
}

void AFightingGameMode::BeginRound()
{
	OnBeginRound();

	Fighters[0]->BeginRound();
	Fighters[1]->BeginRound();
}

void AFightingGameMode::BeginPoint()
{
	OnBeginPoint();

	ResetPositions();

	Fighters[0]->BeginPoint();
	Fighters[1]->BeginPoint();
}

void AFightingGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Fighter0 && Fighter1) {
	//	double Position0 = Fighter0->GetActorLocation().X;
	//	double Position1 = Fighter1->GetActorLocation().X;

	//	// Fighter0 is to the left of Fighter1
	//	if (Position0 < Position1) {
	//		if (!Fighter0->GetIsFacingRight())
	//			Fighter0->FaceDirection(true);
	//		if (Fighter1->GetIsFacingRight())
	//			Fighter1->FaceDirection(false);
	//	}
	//	// Fighter1 is to the left of Fighter0
	//	if (Position1 < Position0) {
	//		if (!Fighter1->GetIsFacingRight())
	//			Fighter1->FaceDirection(true);
	//		if (Fighter0->GetIsFacingRight())
	//			Fighter0->FaceDirection(false);
	//	}
	//}
}

int AFightingGameMode::GetScore(AFighterPawn* FightingComp)
{
	if (FightingComp == Fighters[0])
		return Score[0];
	else if (FightingComp == Fighters[1])
		return Score[1];

	return 0;
}

int AFightingGameMode::GetRound()
{
	return FMath::Clamp(((Score[0] + Score[1]) / 5) + 1, 0, 3);
}
