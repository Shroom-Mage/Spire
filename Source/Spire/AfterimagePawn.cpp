// Fill out your copyright notice in the Description page of Project Settings.


#include "AfterimagePawn.h"
#include "FighterStateAsset.h"

void AAfterimagePawn::EnterState(UFighterStateAsset* State, EVelocityType VelocityType, bool bResetAnimation, bool bSplit)
{
	Super::EnterState(State, VelocityType, bResetAnimation, true);
}
