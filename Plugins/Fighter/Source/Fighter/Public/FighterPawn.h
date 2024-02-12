// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFighterInnateAsset;
class UFighterState;
class UFighterAttackAsset;
class AFightingGameMode;

UCLASS()
class FIGHTER_API AFighterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFighterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to enter a new state. Entering the current state will do nothing.
	UFUNCTION(BlueprintCallable)
	virtual void EnterState(UFighterState* State);

	// Called to enter a new state. Entering the current state will do nothing.
	UFUNCTION(BlueprintCallable)
	virtual void EnterAttackState(UFighterAttackAsset* AttackState);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void BeginMatch();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginMatch")
	void OnBeginMatch();

	UFUNCTION(BlueprintCallable)
	virtual void BeginRound();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginRound")
	void OnBeginRound();

	UFUNCTION(BlueprintCallable)
	virtual void BeginPoint();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="BeginPoint")
	void OnBeginPoint();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	bool GetIsAttackActive();

	UFUNCTION(BlueprintCallable)
	void Move(float Value);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void Crouch(float Value);

	UFUNCTION(BlueprintCallable)
	void Evade();

	UFUNCTION(BlueprintCallable)
	void Normal();

	UFUNCTION(BlueprintCallable)
	void Special();

	UFUNCTION(BlueprintCallable)
	virtual void HardCancel();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="HardCancel")
	void OnHardCancel(UFighterAttackAsset* CanceledAttack, FVector2D CanceledVelocity);

	UFUNCTION(BlueprintCallable)
	void TurnAround();

	UFUNCTION(BlueprintCallable)
	void ResetToNeutral();

	UFUNCTION(BlueprintCallable)
	void FaceDirection(bool bFaceRight);
	
	UFUNCTION(BlueprintCallable)
	virtual void TakeHit(AFighterPawn* Attacker, float Damage);

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetSkeletalMeshComponent();

	UFUNCTION(BlueprintCallable)
	bool GetIsFacingRight();

	UFUNCTION(BlueprintCallable)
	UAnimSequence* GetAnimationSequence();
	
	UFUNCTION(BlueprintCallable)
	float GetAnimationPlayRate();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USceneComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* HipsCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* HeadCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* UpperArmLCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* UpperArmRCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ForearmLCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ForearmRCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ThighLCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ThighRCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ShinLCapsule;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* ShinRCapsule;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	bool bAnimationNeedsReset;

	bool bIsFacingRight = true;
	FVector AttackStartLocation;

	float MovementInput = 0.0f;
	float CrouchInput = 0.0f;
	float JumpInputTime = 0.0f;
	float EvadeInputTime = 0.0f;
	float NormalInputTime = 0.0f;
	float SpecialInputTime = 0.0f;

	AFightingGameMode* GameMode;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	UFighterState* CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	UFighterAttackAsset* CurrentAttackState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	AFighterPawn* Target = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess="true"))
	float CurrentFrame = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	bool bIsAttackActive = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	bool bCanCancelState = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	bool bHasAttackHit = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float Health = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float Resource = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float ResourceMax = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	FVector2D Velocity = { 0.0f, 0.0f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterInnateAsset* InnateAsset;

	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* GroundNeutral;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* GroundForward;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* GroundCrouching;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* AirNeutral;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* AirForward;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* AirCrouching;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* EvadeNeutral;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* EvadeForward;
	UPROPERTY(BlueprintReadWrite, Category="Core States")
	UFighterState* EvadeCrouching;
};
