// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterCommand.h"
#include "FighterStateAsset.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterStateAsset : public UDataAsset
{
	GENERATED_BODY()

	UFighterStateAsset() {
		Transitions.Add(FighterCommand::ATTACK_NORMAL);
		Transitions.Add(FighterCommand::ATTACK_SPECIAL);
		Transitions.Add(FighterCommand::FORWARD);
		Transitions.Add(FighterCommand::BACKWARD);
		Transitions.Add(FighterCommand::DASH_FORWARD);
		Transitions.Add(FighterCommand::DASH_BACKWARD);
		Transitions.Add(FighterCommand::JUMP);
		Transitions.Add(FighterCommand::CROUCH);
		Transitions.Add(FighterCommand::DODGE);
		Transitions.Add(FighterCommand::GROUND);
		Transitions.Add(FighterCommand::END);
	}

	UPROPERTY(EditAnywhere)
	float Duration;
	UPROPERTY(EditAnywhere)
	bool bRelativeVelocity;
	FVector2D Shift;
	UPROPERTY(EditAnywhere)
	FVector2D VelocityInitial;
	UPROPERTY(EditAnywhere)
	FVector2D VelocityTarget;
	UPROPERTY(EditAnywhere)
	FVector2D Acceleration;
	UPROPERTY(EditAnywhere)
	FVector2D Deceleration;
	UPROPERTY(EditAnywhere)
	TMap<FighterCommand, UFighterStateAsset*> Transitions;
};
