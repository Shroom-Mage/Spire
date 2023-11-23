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

	for (UArcanaEffect* Effect : ActiveEffects) {
		Effect->BeginMatch();
	}
}

void ASpireGameMode::BeginRound()
{
	Super::BeginRound();

	for (UArcanaEffect* Effect : ActiveEffects) {
		Effect->BeginRound();
	}
}

void ASpireGameMode::BeginPoint()
{
	Super::BeginPoint();

	for (UArcanaEffect* Effect : ActiveEffects) {
		Effect->BeginPoint();
	}
}
