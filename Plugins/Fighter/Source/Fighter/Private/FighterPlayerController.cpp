// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPlayerController.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//#include "InputActionValue.h"

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

	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
	//	// Movement
	//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, Fighter, &AFighterPawn::Move);
	//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, Fighter, &AFighterPawn::Jump);
	//	EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Started, Fighter, &AFighterPawn::Evade);

	//	// Attacks
	//	EnhancedInputComponent->BindAction(NormalAction, ETriggerEvent::Started, Fighter, &AFighterPawn::Normal);
	//	EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Started, Fighter, &AFighterPawn::Special);
	//}

	//AFighterPawn* Fighter = Cast<AFighterPawn>(Owner);

	//InputComponent->BindAxis("Move", Fighter, &AFighterPawn::Move);
	//InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Jump);
	//InputComponent->BindAction("Evade", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Evade);
	//InputComponent->BindAction("Normal", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Normal);
	//InputComponent->BindAction("Special", EInputEvent::IE_Pressed, Fighter, &AFighterPawn::Special);
}
