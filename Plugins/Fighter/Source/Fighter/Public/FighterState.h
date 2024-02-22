// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FighterState.generated.h"

UENUM(BlueprintType, DisplayName="Fighter State")
enum class EFighterState : uint8
{
	GroundNeutral,
	GroundForward,
	GroundCrouching,
	AirNeutral,
	AirForward,
	AirCrouching,
	EvadeNeutral,
	EvadeForward,
	EvadeCrouching,
	Attack
};
