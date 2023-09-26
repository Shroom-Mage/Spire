// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterStateAsset.generated.h"

USTRUCT()
struct FFighterStateTransition
{
	GENERATED_BODY()

	// The state to enter
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* State;
	// If bSplit is true, StateTime will not be reset upon entering this state.
	UPROPERTY(EditAnywhere)
	bool bSplit;
	// If bInterruptAnimation is true, this state's animation will play instantly instead of blending.
	UPROPERTY(EditAnywhere)
	bool bInterruptAnimation;
	// If bInheritVelocity is true, VelocityInitial will be added to Velocity instead of replacing it.
	UPROPERTY(EditAnywhere)
	bool bInheritVelocity;
};

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterStateAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// When Duration is reached (in seconds), the state will end.
	UPROPERTY(EditAnywhere)
	float Duration;
	// When entering this state, Shift is distance to translate irrespective of Velocity.
	UPROPERTY(EditAnywhere)
	FVector2D Shift;
	// When entering this state, VelocityInitial will be added to or assigned to the actor's Velocity.
	UPROPERTY(EditAnywhere)
	FVector2D VelocityInitial;
	// The actor will accelerate or decelerate to reach VelocityTarget.
	UPROPERTY(EditAnywhere)
	FVector2D VelocityTarget;
	// If the actor's Velocity is less than this state's VelocityTarget, Acceleration is applied.
	UPROPERTY(EditAnywhere)
	FVector2D Acceleration;
	// If the actor's Velocity is less than this state's VelocityTarget, Deceleration is applied.
	UPROPERTY(EditAnywhere)
	FVector2D Deceleration;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition AttackNormal;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition AttackSpecial;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition WalkForward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition WalkBackward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition DashForward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition DashBackward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Jump;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Crouch;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Dodge;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Land;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition End;
};
