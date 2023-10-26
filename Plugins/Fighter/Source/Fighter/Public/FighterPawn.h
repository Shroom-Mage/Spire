// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	void Move(const struct FInputActionValue& Value);

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

	UFUNCTION(BlueprintCallable, CallInEditor)
	void TurnAround();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	USceneComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UBoxComponent* BodyBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	UBoxComponent* AttackBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* Camera;

	bool bIsFacingRight = true;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UFightingComponent* Fighting;
};
