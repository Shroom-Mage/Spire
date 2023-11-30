// Fill out your copyright notice in the Description page of Project Settings.


#include "SpireGameMode.h"
#include "ArcanaAsset.h"

void ASpireGameMode::DrawCard()
{
	// Draw card from the top
	UArcanaAsset* Card = ArcanaDeck.Pop();
	ActiveArcana.Add(Card);

	// Create an effect from the card
	UArcanaEffect* Effect = NewObject<UArcanaEffect>(this, Card->Effect);
	Effect->Match = this;
	ActiveEffects.Add(Effect);
}

void ASpireGameMode::BeginMatch()
{
	for (UArcanaAsset* Card : ActiveArcana) {
		ArcanaDeck.Add(Card);
	}

	Super::BeginMatch();

	// Draw five cards
	DrawCard();
	DrawCard();
	DrawCard();
	DrawCard();
	DrawCard();

	for (int i = 0; i < GetRound() + 2 && i < ActiveEffects.Num(); i++) {
		ActiveEffects[i]->BeginPoint();
	}
}

void ASpireGameMode::BeginRound()
{
	Super::BeginRound();

	for (int i = 0; i < GetRound() + 2 && i < ActiveEffects.Num(); i++) {
		ActiveEffects[i]->BeginRound();
	}
}

void ASpireGameMode::BeginPoint()
{
	Super::BeginPoint();

	for (int i = 0; i < GetRound() + 2 && i < ActiveEffects.Num(); i++) {
		ActiveEffects[i]->BeginPoint();
	}
}
