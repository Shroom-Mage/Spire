// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FightingComponent = CreateDefaultSubobject<UFightingComponent>(TEXT("FightingComponent"));
}

// Called when the game starts or when spawned
void AFighterPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFighterPawn::Normal()
{
	FightingComponent->Normal();
}

void AFighterPawn::Special()
{
	FightingComponent->Special();
}

void AFighterPawn::Move(float Value)
{
	FightingComponent->Move(Value);
}

void AFighterPawn::Jump()
{
	FightingComponent->Jump();
}

void AFighterPawn::Evade()
{
	FightingComponent->Evade();
}
