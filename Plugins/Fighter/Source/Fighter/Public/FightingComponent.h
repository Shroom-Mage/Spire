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
	void EnterStateTransition(FFighterStateTransition Transition);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetBodyBox(UBoxComponent* BodyBox);

	void SetAttackBox(UBoxComponent* AttackBox);

	UFUNCTION(BlueprintCallable)
	void Normal();

	UFUNCTION(BlueprintCallable)
	void Special();
	
	UFUNCTION(BlueprintCallable)
	void Move(float Value);

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void Evade();

public:
	UPROPERTY(EditAnywhere)
	UFighterStateAsset* CurrentState;
	UPROPERTY(EditAnywhere)
	FVector2D Velocity = {0.0f, 0.0f};
	UPROPERTY(VisibleAnywhere)
	float StateTime = 0.0f;
	UPROPERTY(VisibleAnywhere)
	bool bIsAttackActive = false;
	UPROPERTY(VisibleAnywhere)
	bool bCanCancelState = false;


private:
	float Movement = 0.0f;
	UBoxComponent* OwnerBodyBoxComponent;
	UBoxComponent* OwnerAttackBoxComponent;
};
