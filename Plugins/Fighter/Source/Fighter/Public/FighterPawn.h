// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FighterPawn.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UFighterStateAsset;
class UFighterAttackStateAsset;
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

	UFUNCTION(BlueprintCallable)
	// Called to enter a new state. Entering the current state will do nothing.
	virtual void EnterState(UFighterStateAsset* State, EVelocityType VelocityType, bool bSplit = false);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="EnterState")
	void OnEnterState(UFighterStateAsset* StateEntered, UFighterStateAsset* StateExited);

	virtual void EnterAttackState(UFighterAttackStateAsset* AttackState, EVelocityType VelocityType, bool bSplit = false);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="EnterAttackState")
	void OnEnterAttackState(UFighterAttackStateAsset* StateEntered, UFighterStateAsset* StateExited);

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
	void Evade();

	UFUNCTION(BlueprintCallable)
	void Normal();

	UFUNCTION(BlueprintCallable)
	void Special();

	UFUNCTION(BlueprintCallable)
	virtual void HardCancel();

	UFUNCTION(BlueprintImplementableEvent, DisplayName="HardCancel")
	void OnHardCancel(UFighterStateAsset* CanceledState, FVector2D CanceledVelocity);

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

	UFUNCTION(BlueprintCallable)
	bool GetLoopAnimation();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USceneComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UBoxComponent* BodyBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UBoxComponent* AttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	bool bAnimationNeedsReset;

	bool bIsFacingRight = true;

	float MovementInput = 0.0f;
	float JumpInputTime = 0.0f;
	float EvadeInputTime = 0.0f;
	float NormalInputTime = 0.0f;
	float SpecialInputTime = 0.0f;

	AFightingGameMode* GameMode;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Status", meta = (AllowPrivateAccess = "true"))
	UFighterStateAsset* CurrentState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta = (AllowPrivateAccess = "true"))
	UFighterAttackStateAsset* CurrentAttackState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	AFighterPawn* Target = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Status", meta=(AllowPrivateAccess="true"))
	float StateTime = 0.0f;
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
	FVector2D Velocity = {0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* GroundNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* GroundForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* GroundCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeCrouching;
};
