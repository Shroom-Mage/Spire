// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "FighterStateAsset.h"
#include "FightingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTER_API UFightingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFightingComponent();

private:
	// Called to enter a new state. Entering the current state will do nothing.
	void EnterStateTransition(UFighterStateAsset* State, EVelocityType VelocityType, bool bResetAnimation = false, bool bSplit = false);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetBodyBox(UBoxComponent* BodyBox);

	void SetAttackBox(UBoxComponent* AttackBox);

	void SetSkeletalMesh(USkeletalMeshComponent* SkeletalMesh);

	bool GetIsAttackActive();

	UFUNCTION()
	void OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float Resource = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	UFighterStateAsset* CurrentState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Status")
	FVector2D Velocity = {0.0f, 0.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* StandingNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* StandingForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* StandingBackward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* CrouchingNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* AirBackward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeNeutral;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Core States")
	UFighterStateAsset* EvadeBackward;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	UFightingComponent* Target = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	float StateTime = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	bool bIsAttackActive = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Status", meta=(AllowPrivateAccess="true"))
	bool bCanCancelState = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation", meta=(AllowPrivateAccess="true"))
	UAnimSequence* CurrentAnimation = nullptr;

	float MovementInput = 0.0f;
	float JumpInputTime = 0.0f;
	float EvadeInputTime = 0.0f;
	float NormalInputTime = 0.0f;
	float SpecialInputTime = 0.0f;
	UBoxComponent* OwnerBodyBox = nullptr;
	UBoxComponent* OwnerAttackBox = nullptr;
	USkeletalMeshComponent* OwnerSkeletalMesh = nullptr;
};
