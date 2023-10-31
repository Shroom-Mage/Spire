// Fill out your copyright notice in the Description page of Project Settings.


#include "FightingGameMode.h"
#include "FightingComponent.h"

void AFightingGameMode::AddPoint(UFightingComponent* Recipient)
{
	if (Recipient == Fighter0)
		Score0++;
	else if (Recipient == Fighter1)
		Score1++;
}

int AFightingGameMode::GetScore(UFightingComponent* Recipient)
{
	if (Recipient == Fighter0)
		return Score0;
	else if (Recipient == Fighter1)
		return Score1;

	return 0;
}
