// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "FightingGameMode.h"
#include "FighterStateAsset.h"
#include "FighterAttackStateAsset.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Base);

	BodyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBox"));
	BodyBox->SetupAttachment(Base);
	BodyBox->ShapeColor = FColor(0, 0, 255, 255);

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetupAttachment(Base);
	AttackBox->ShapeColor = FColor(255, 0, 0, 255);
	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AFighterPawn::OnAttackOverlapBegin);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &AFighterPawn::OnAttackOverlapEnd);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Base);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AFighterPawn::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AFightingGameMode>(GetWorld()->GetAuthGameMode());
}

void AFighterPawn::EnterState(UFighterStateAsset* State, EVelocityType VelocityType, bool bSplit)
{
	if (State == CurrentState || State == nullptr)
		return;

	UFighterStateAsset* PreviousState = CurrentState;
	CurrentState = State;
	if (!CurrentState->GetIsAttack()) {
		CurrentAttackState = nullptr;
	}

	// Adjust body box
	FVector BodyBoxLocation = FVector(State->BodyBoxLocation.X, 0.0f, State->BodyBoxLocation.Y);
	FVector BodyBoxExtent = FVector(State->BodyBoxExtent.X, 0.0f, State->BodyBoxExtent.Y);
	BodyBox->SetRelativeLocation(BodyBoxLocation);
	BodyBox->SetBoxExtent(BodyBoxExtent);

	// Apply initial velocity
	switch (VelocityType) {
	case EVelocityType::ADD:
		Velocity += State->VelocityInitial;
		break;
	case EVelocityType::REPLACE:
		Velocity = State->VelocityInitial;
		break;
	default:
		break;
	}

	// Reset time
	if (!bSplit)
		StateTime = 0.0f;

	// Gain resource
	Resource = FMathf::Clamp(Resource + State->ResourceGain * GameMode->ResourceMultiplier, 0.0f, ResourceMax);
	if (State->ResourceGain > 0.0f)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Resource: %f"), Resource));

	OnEnterState(CurrentState, PreviousState);
}

void AFighterPawn::EnterAttackState(UFighterAttackStateAsset* AttackState, EVelocityType VelocityType, bool bSplit)
{
	UFighterStateAsset* PreviousState = CurrentState;
	CurrentAttackState = AttackState;

	// Adjust attack box
	FVector AttackBoxLocation = FVector(AttackState->AttackBoxLocation.X, 0.0f, AttackState->AttackBoxLocation.Y);
	FVector AttackBoxExtent = FVector(AttackState->AttackBoxExtent.X, 0.0f, AttackState->AttackBoxExtent.Y);
	AttackBox->SetRelativeLocation(AttackBoxLocation);
	AttackBox->SetBoxExtent(AttackBoxExtent);
	bHasAttackHit = false;

	EnterState(AttackState, VelocityType, bSplit);

	OnEnterAttackState(CurrentAttackState, PreviousState);
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentState)
		return;

	// Update timers
	StateTime += DeltaTime;
	JumpInputTime -= DeltaTime;
	EvadeInputTime -= DeltaTime;
	NormalInputTime -= DeltaTime;
	SpecialInputTime -= DeltaTime;

	// Set attack activity
	if (CurrentAttackState) {
		if (StateTime > CurrentAttackState->ActiveStartTime && StateTime < CurrentAttackState->ActiveEndTime && !bHasAttackHit) {
			bIsAttackActive = true;
			AttackBox->ShapeColor.A = 255;
			// Check for opponent and hit
			if (Target) {
				bHasAttackHit = true;
				Target->TakeHit(this, 1.0f);
			}
		}
		else {
			bIsAttackActive = false;
			AttackBox->ShapeColor.A = 0;
		}
	}

	// Approach target velocity
	if (Velocity.X <= CurrentState->VelocityTarget.X - CurrentState->Acceleration.X * DeltaTime) {
		Velocity.X += CurrentState->Acceleration.X * DeltaTime;
	}
	else if (Velocity.X >= CurrentState->VelocityTarget.X + CurrentState->Deceleration.X * DeltaTime) {
		Velocity.X -= CurrentState->Deceleration.X * DeltaTime;
	}
	else {
		Velocity.X = CurrentState->VelocityTarget.X;
	}
	if (Velocity.Y <= CurrentState->VelocityTarget.Y - CurrentState->Acceleration.Y * DeltaTime) {
		Velocity.Y += CurrentState->Acceleration.Y * DeltaTime;
	}
	else if (Velocity.Y >= CurrentState->VelocityTarget.Y + CurrentState->Deceleration.Y * DeltaTime) {
		Velocity.Y -= CurrentState->Deceleration.Y * DeltaTime;
	}
	else {
		Velocity.Y = CurrentState->VelocityTarget.Y;
	}

	// Translate
	FVector Location = GetActorLocation();
	FVector Destination = Location + FVector(Velocity.X * GetActorForwardVector().X, 0.0f, Velocity.Y);
	bool bTouchedGround = Destination.Z <= 0.0;
	if (bTouchedGround) {
		Destination.Z = 0.0;
		Velocity.Y = 0.0;
	}
	SetActorLocation(Destination);

	// Cancel state
	if (CurrentAttackState) {
		if (CurrentAttackState->CancelTime > 0.0f
			&& StateTime > CurrentAttackState->CancelTime
			&& (MovementInput < 0.0f
				|| MovementInput > 0.0f
				|| JumpInputTime > 0.0f
				|| EvadeInputTime > 0.0f
				|| NormalInputTime > 0.0f
				|| SpecialInputTime > 0.0f))
		{
			if (bTouchedGround)
				CurrentState = GroundNeutral;
			else
				CurrentState = AirNeutral;
		}
	}

	// Attacking (Normal)
	if (NormalInputTime > 0.0f
		&& CurrentState->AttackNormal)
	{
		NormalInputTime = 0.0f;
		EnterAttackState(CurrentState->AttackNormal, EVelocityType::ADD);
		return;
	}
	// Jumping
	else if ((CurrentState == GroundNeutral
		|| CurrentState == GroundForward
		|| CurrentState == GroundCrouching)
		&& bTouchedGround
		&& JumpInputTime > 0.0f
		&& AirNeutral)
	{
		JumpInputTime = 0.0f;
		EnterState(AirNeutral, EVelocityType::ADD);
		return;
	}
	// Landing
	else if ((CurrentState == AirNeutral
		|| CurrentState == AirForward
		|| CurrentState == AirCrouching)
		&& bTouchedGround
		&& GroundNeutral)
	{
		EnterState(GroundNeutral, EVelocityType::ADD);
		return;
	}
	// Crouching (Ground)
	else if ((CurrentState == GroundNeutral
		|| CurrentState == GroundForward
		|| CurrentState == GroundCrouching)
		&& CrouchInput > 0.0f
		&& GroundCrouching)
	{
		EnterState(GroundCrouching, EVelocityType::IGNORE);
		return;
	}
	// Moving (Ground)
	if ((CurrentState == GroundNeutral
		|| CurrentState == GroundForward
		|| CurrentState == GroundCrouching)
		&& MovementInput != 0.0f
		&& CrouchInput == 0.0f
		&& GroundForward)
	{
		if (MovementInput < 0.0f) {
			TurnAround();
		}
		EnterState(GroundForward, EVelocityType::IGNORE);
		return;
	}
	// Stopping (Ground)
	if ((CurrentState == GroundNeutral
		|| CurrentState == GroundForward
		|| CurrentState == GroundCrouching)
		&& MovementInput == 0.0f
		&& GroundNeutral)
	{
		EnterState(GroundNeutral, EVelocityType::IGNORE);
		return;
	}
	// Crouching (Air)
	if ((CurrentState == AirNeutral
		|| CurrentState == AirForward
		|| CurrentState == AirCrouching)
		&& CrouchInput> 0.0f
		&& AirCrouching)
	{
		EnterState(AirCrouching, EVelocityType::IGNORE);
		return;
	}
	// Moving (Air)
	if ((CurrentState == AirNeutral
		|| CurrentState == AirForward)
		&& MovementInput != 0.0f
		&& AirForward)
	{
		if (MovementInput < 0.0f) {
			TurnAround();
		}
		EnterState(AirForward, EVelocityType::IGNORE);
		return;
	}
	// Stopping (Air)
	if ((CurrentState == AirNeutral
		|| CurrentState == AirForward)
		&& MovementInput == 0.0f
		&& AirNeutral)
	{
		EnterState(AirNeutral, EVelocityType::IGNORE);
		return;
	}
	// Ending
	if (CurrentState->Duration > 0.0f
		&& StateTime >= CurrentState->Duration
		&& CurrentState->End)
	{
		EnterState(CurrentState->End, EVelocityType::IGNORE);
		return;
	}
}

void AFighterPawn::BeginMatch()
{
	OnBeginMatch();
}

void AFighterPawn::BeginRound()
{
	OnBeginRound();
}

void AFighterPawn::BeginPoint()
{
	OnBeginPoint();
}

// Called to bind functionality to input
void AFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFighterPawn::OnAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "Pawn OverlapBegin from " + OverlappedComp->GetFName().ToString() + " to " + OtherComp->GetFName().ToString());
	if (OtherComp->GetFName() == TEXT("BodyBox")) {
		AFighterPawn* OtherFighter = Cast<AFighterPawn>(OtherActor);
		if (OtherFighter != this)
			Target = OtherFighter;
	}
}

void AFighterPawn::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "Pawn OverlapEnd from " + OverlappedComp->GetFName().ToString() + " to " + OtherComp->GetFName().ToString());
	if (OtherComp->GetFName() == TEXT("BodyBox")) {
		AFighterPawn* OtherFighter = Cast<AFighterPawn>(OtherActor);
		if (OtherFighter == Target)
			Target = nullptr;
	}
}

bool AFighterPawn::GetIsAttackActive()
{
	return bIsAttackActive;
}

void AFighterPawn::Move(float Value)
{
	MovementInput = bIsFacingRight ? Value : -Value;
}

void AFighterPawn::Jump()
{
	JumpInputTime = 0.25f;
}

void AFighterPawn::Crouch(float Value)
{
	CrouchInput = Value;
}

void AFighterPawn::Evade()
{
	EvadeInputTime = 0.5f;
}

void AFighterPawn::Normal()
{
	NormalInputTime = 0.5f;
}

void AFighterPawn::Special()
{
	SpecialInputTime = 0.5f;
}

void AFighterPawn::HardCancel()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Resource: %f"), Resource));

	if (Resource < 1.0f)
		return;

	Resource--;
	FVector2D CanceledVelocity = Velocity;
	UFighterStateAsset* CanceledState = CurrentState;

	ResetToNeutral();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HARD CANCEL!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Resource: %f"), Resource));

	if (CanceledState)
		OnHardCancel(CanceledState, CanceledVelocity);
}

void AFighterPawn::TurnAround()
{
	bIsFacingRight = !bIsFacingRight;

	Velocity.X *= -1.0f;

	if (bIsFacingRight) {
		SetActorRelativeRotation(FRotator(0.0, 0.0, 0.0));
		SpringArm->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	}
	else {
		SetActorRelativeRotation(FRotator(0.0, 180.0, 0.0));
		SpringArm->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
	}
}

void AFighterPawn::ResetToNeutral()
{
	FVector Location = GetActorLocation();
	bool bTouchingGround = Location.Z <= 0.0;

	Velocity = { 0.0f, 0.0f };
	if (bTouchingGround) {
		EnterState(GroundNeutral, EVelocityType::IGNORE, true);
	}
	else {
		EnterState(AirNeutral, EVelocityType::IGNORE, true);
	}
}

void AFighterPawn::FaceDirection(bool bFaceRight)
{
	if (bIsFacingRight == bFaceRight)
		return;

	TurnAround();
}

void AFighterPawn::TakeHit(AFighterPawn* Attacker, float Damage)
{
	if (Attacker->Owner == this)
		return;

	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HIT!"));
	// Increment the score
	if (GameMode) {
		GameMode->RegisterHit(Attacker, this);
	}
}

USkeletalMeshComponent* AFighterPawn::GetSkeletalMeshComponent()
{
	return SkeletalMesh;
}

bool AFighterPawn::GetIsFacingRight()
{
	return bIsFacingRight;
}

UAnimSequence* AFighterPawn::GetAnimationSequence()
{
	if (!CurrentState->GetIsAttack()) {
		return CurrentState->AnimationLoop;
	}
	else if (StateTime < CurrentAttackState->ActiveStartTime) {
		return CurrentAttackState->AnimationLead;
	}
	else {
		return CurrentAttackState->AnimationFollow;
	}
}

float AFighterPawn::GetAnimationPlayRate()
{
	if (!CurrentState->GetIsAttack()) {
		return 1.0f;
	}
	else if (StateTime < CurrentAttackState->ActiveStartTime) {
		return 1.0f / (CurrentAttackState->ActiveStartTime);
	}
	else {
		return 1.0f / (CurrentAttackState->Duration - CurrentAttackState->ActiveStartTime);
	}
}

bool AFighterPawn::GetLoopAnimation()
{
	if (!CurrentState->GetIsAttack()) {
		return CurrentState->bLoopAnimation;
	}
	else {
		return false;
	}
}
