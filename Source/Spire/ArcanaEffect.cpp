// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcanaEffect.h"
#include "FightingGameMode.h"

void UArcanaEffect::BeginMatch()
{
	OnBeginMatch();
}

void UArcanaEffect::BeginRound()
{
	OnBeginRound();
}

void UArcanaEffect::BeginPoint()
{
	OnBeginPoint();
}
