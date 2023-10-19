// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPlayerController.h"

void AFighterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AFighterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFighterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//AFighterPawn* Fighter = Cast<AFighterPawn>(Owner);

	//InputComponent->BindAxis("Move", Fighter, &AFighterPawn::Move);
	//InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Jump);
	//InputComponent->BindAction("Evade", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Evade);
	//InputComponent->BindAction("Normal", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Normal);
	//InputComponent->BindAction("Special", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Special);
}
