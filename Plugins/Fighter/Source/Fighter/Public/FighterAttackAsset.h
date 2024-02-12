// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FighterAttackAsset.generated.h"

class UFighterState;

/**
 * 
 */
UCLASS()
class FIGHTER_API UFighterAttackAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AnimationLead;
	// The animation to play when entering the state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AnimationFollow;
	// The number of frames at 60f/s before attack box becomes active.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	int32 StartupFrames = 0;
	// The number of frames at 60f/s that the attack box is active.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	int32 ActiveFrames = 0;
	// The number of frames at 60f/s after attack box is active.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	int32 RecoveryFrames = 0;
	// CancelFrame is the first frame (at 60f/s) that an attack will be canceled freely.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	int32 CancelFrame = 0;
	// The location of the attack.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	FName SocketName;
	// The radius of the attack.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	float Radius;
	// When the state is entered, the fighter gains resource equal to ResourceGain.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource")
	float ResourceGain = 0.0f;
	// When entering this state, ShiftStart is distance to translate irrespective of Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsAir;
	// When entering this state, ShiftStart is distance to translate irrespective of Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D ShiftStart;
	// When exiting this state, ShiftEnd is distance to translate irrespective of Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D ShiftEnd;
	// When entering this state, VelocityInitial will be applied to the actor's Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D VelocityInitial;
	// The actor will accelerate or decelerate to reach VelocityTarget.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D VelocityTarget;
	// If the actor's Velocity is less than this state's VelocityTarget, Acceleration is added to Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D Acceleration;
	// If the actor's Velocity is less than this state's VelocityTarget, Deceleration is subtracted from Velocity.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	FVector2D Deceleration;
	// When CurrentFrame has reached the Duration, the fighter will enter this state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chaining")
	UFighterState* End;
};
