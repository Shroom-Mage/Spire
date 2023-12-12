// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterStateAsset.generated.h"


UENUM()
enum class EVelocityType : uint8
{
	IGNORE,
	ADD,
	REPLACE
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
	UPROPERTY(EditAnywhere, Category="Timing")
	float Duration;
	// The state time at which the attack box becomes active.
	UPROPERTY(EditAnywhere, Category="Timing")
	float ActiveStartTime = 0.0f;
	// The state time at which the attack box becomes inactive.
	UPROPERTY(EditAnywhere, Category="Timing")
	float ActiveEndTime = 0.0f;
	// When CancelTime is reached (in seconds), the state may be changed.
	UPROPERTY(EditAnywhere, Category="Timing")
	float CancelTime = 0.0f;
	// When the state is entered, the fighter gains resource equal to ResourceGain.
	UPROPERTY(EditAnywhere, Category="Resource")
	float ResourceGain = 0.0f;
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
	// The location of the body collider.
	UPROPERTY(EditAnywhere, Category="Collision")
	FVector2D BodyBoxLocation;
	// The extent of the body collider.
	UPROPERTY(EditAnywhere, Category="Collision")
	FVector2D BodyBoxExtent;
	// The location of the attack collider.
	UPROPERTY(EditAnywhere, Category="Collision")
	FVector2D AttackBoxLocation;
	// The extent of the attack collider.
	UPROPERTY(EditAnywhere, Category="Collision")
	FVector2D AttackBoxExtent;
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, Category="Animation")
	UAnimSequence* Animation;
	// BlendTime is the amount of time in seconds to change from the previous animation to the new one.
	UPROPERTY(EditAnywhere, Category="Animation")
	float BlendTime = 0.0f;
	// Whether to repeat the animation while in the state.
	UPROPERTY(EditAnywhere, Category="Animation")
	bool bLoopAnimation;
	// When the attack button is pressed, the fighter will enter this state.
	UPROPERTY(EditAnywhere, Category="Attack")
	UFighterStateAsset* AttackNormal;
	// When StateTime has reached the Duration, the fighter will enter this state.
	UPROPERTY(EditAnywhere, Category="Timing")
	UFighterStateAsset* End;
};
