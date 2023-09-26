// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FightingComponent.h"
#include "FighterPawn.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, CallInEditor)
	void AttackNormal();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void AttackSpecial();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void WalkForward();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void WalkBackward();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void DashForward();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void DashBackward();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Jump();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Crouch();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Dodge();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void Land();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFightingComponent* FightingComponent;

};
