// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterStateAsset.generated.h"


UENUM()
enum class EVelocityType
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
	// VelocityType determines how to apply VelocityInitial to Velocity.
	UPROPERTY(EditAnywhere)
	EVelocityType VelocityType;
};

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterStateAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	// The location of the body collider.
	UPROPERTY(EditAnywhere, Category="Combat")
	FVector2D BodyBoxLocation;
	// The extent of the body collider.
	UPROPERTY(EditAnywhere, Category="Combat")
	FVector2D BodyBoxExtent;
	// The location of the attack collider.
	UPROPERTY(EditAnywhere, Category="Combat")
	FVector2D AttackBoxLocation;
	// The extent of the attack collider.
	UPROPERTY(EditAnywhere, Category="Combat")
	FVector2D AttackBoxExtent;
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimSequence* Animation;
	// Whether to repeat the animation while in the state.
	UPROPERTY(EditAnywhere, Category="Animation")
	bool bLoopAnimation;
	// When Duration is reached (in seconds), the state will end.
	UPROPERTY(EditAnywhere)
	float Duration;
	// When CancelTime is reached (in seconds), the state may be changed.
	UPROPERTY(EditAnywhere)
	float CancelTime = 0.0f;
	// The state time at which the attack box becomes active.
	UPROPERTY(EditAnywhere, Category="Combat")
	float ActiveStartTime = 0.0f;
	// The state time at which the attack box becomes inactive.
	UPROPERTY(EditAnywhere, Category="Combat")
	float ActiveEndTime = 0.0f;
	// When entering this state, Shift is distance to translate irrespective of Velocity.
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D Shift;
	// When entering this state, VelocityInitial will be applied to the actor's Velocity.
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D VelocityInitial;
	// The actor will accelerate or decelerate to reach VelocityTarget.
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D VelocityTarget;
	// If the actor's Velocity is less than this state's VelocityTarget, Acceleration is added to Velocity.
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D Acceleration;
	// If the actor's Velocity is less than this state's VelocityTarget, Deceleration is subtracted from Velocity.
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector2D Deceleration;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Normal;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Special;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Forward;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Backward;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Jump;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Dodge;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition Land;
	UPROPERTY(EditAnywhere, Category="Transition")
	FFighterStateTransition End;
};
