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
	UFighterStateAsset();

public:
	UFUNCTION(BlueprintCallable)
	bool GetIsAttack() { return bIsAttack; }

protected:
	// The state is regarded as an attack if bIsAttack is true.
	UPROPERTY(VisibleAnywhere, Category="Attack", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack = false;

public:
	// When Duration is reached (in seconds), the state will end.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Timing")
	float Duration;
	// The location of the body collider.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	FVector2D BodyBoxLocation;
	// The extent of the body collider.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Collision")
	FVector2D BodyBoxExtent;
	// When a non-attack state is entered, AnimationLoop will play until the state ends.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	UAnimSequence* AnimationLoop;
	// BlendTime is the amount of time in seconds to change from the previous animation to the new one.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	float BlendTime = 0.0f;
	// Whether to repeat the animation while in the state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	bool bLoopAnimation;
	// When the state is entered, the fighter gains resource equal to ResourceGain.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Resource")
	float ResourceGain = 0.0f;
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
	// When the attack button is pressed, the fighter will enter this state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chaining")
	class UFighterAttackStateAsset* AttackNormal;
	// When StateTime has reached the Duration, the fighter will enter this state.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Chaining")
	UFighterStateAsset* End;
};
