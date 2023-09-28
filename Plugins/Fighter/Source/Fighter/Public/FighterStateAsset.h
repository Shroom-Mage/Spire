// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterStateAsset.generated.h"


UENUM()
enum class VelocityType
{
	IGNORE = 0,
	ADD,
	REPLACE
};

USTRUCT()
struct FFighterStateTransition
{
	GENERATED_BODY()

	// The state to enter
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* State = nullptr;
	// BlendTime is the amount of time in seconds to change from the previous animation to the new one.
	UPROPERTY(EditAnywhere)
	float BlendTime = 0.0f;
	// If bSplit is true, StateTime will not be reset upon entering this state.
	UPROPERTY(EditAnywhere)
	bool bSplit = false;
	// InitialVelocity determines how to apply VelocityInitial to Velocity.
	UPROPERTY(EditAnywhere)
	VelocityType InitialVelocity;
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
	// When entering this state, VelocityInitial will be applied to the actor's Velocity.
	UPROPERTY(EditAnywhere)
	FVector2D VelocityInitial;
	// The actor will accelerate or decelerate to reach VelocityTarget.
	UPROPERTY(EditAnywhere)
	FVector2D VelocityTarget;
	// If the actor's Velocity is less than this state's VelocityTarget, Acceleration is added to Velocity.
	UPROPERTY(EditAnywhere)
	FVector2D Acceleration;
	// If the actor's Velocity is less than this state's VelocityTarget, Deceleration is subtracted from Velocity.
	UPROPERTY(EditAnywhere)
	FVector2D Deceleration;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Normal;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Special;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Forward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Backward;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Jump;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Dodge;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition Land;
	UPROPERTY(EditAnywhere)
	FFighterStateTransition End;
};
