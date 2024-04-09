// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "FightingGameMode.h"
#include "FighterInnateAsset.h"
#include "FighterState.h"
#include "FighterAttackAsset.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Base);

	// Hips
	HipsCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HipsCapsule"));
	HipsCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hips"));
	HipsCapsule->SetRelativeLocationAndRotation(FVector(0.3, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	HipsCapsule->SetCapsuleRadius(0.15f);
	HipsCapsule->SetCapsuleHalfHeight(0.3f);
	HipsCapsule->SetCollisionProfileName(FName("FighterBody"));
	HipsCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Head
	HeadCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HeadCapsule"));
	HeadCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));
	HeadCapsule->SetRelativeLocationAndRotation(FVector(0.1, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	HeadCapsule->SetCapsuleRadius(0.125f);
	HeadCapsule->SetCapsuleHalfHeight(0.125f);
	HeadCapsule->SetCollisionProfileName(FName("FighterBody"));
	HeadCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Upper Arm L
	UpperArmLCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpperArmLCapsule"));
	UpperArmLCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("upper_arm_L"));
	UpperArmLCapsule->SetRelativeLocationAndRotation(FVector(0.15, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	UpperArmLCapsule->SetCapsuleRadius(0.05f);
	UpperArmLCapsule->SetCapsuleHalfHeight(0.2f);
	UpperArmLCapsule->SetCollisionProfileName(FName("FighterBody"));
	UpperArmLCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Upper Arm R
	UpperArmRCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpperArmRCapsule"));
	UpperArmRCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("upper_arm_R"));
	UpperArmRCapsule->SetRelativeLocationAndRotation(FVector(0.15, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	UpperArmRCapsule->SetCapsuleRadius(0.05f);
	UpperArmRCapsule->SetCapsuleHalfHeight(0.2f);
	UpperArmRCapsule->SetCollisionProfileName(FName("FighterBody"));
	UpperArmRCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Forearm L
	ForearmLCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ForearmLCapsule"));
	ForearmLCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("forearm_L"));
	ForearmLCapsule->SetRelativeLocationAndRotation(FVector(0.15, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ForearmLCapsule->SetCapsuleRadius(0.05f);
	ForearmLCapsule->SetCapsuleHalfHeight(0.2f);
	ForearmLCapsule->SetCollisionProfileName(FName("FighterBody"));
	ForearmLCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Forearm R
	ForearmRCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ForearmRCapsule"));
	ForearmRCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("forearm_R"));
	ForearmRCapsule->SetRelativeLocationAndRotation(FVector(0.15, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ForearmRCapsule->SetCapsuleRadius(0.05f);
	ForearmRCapsule->SetCapsuleHalfHeight(0.2f);
	ForearmRCapsule->SetCollisionProfileName(FName("FighterBody"));
	ForearmRCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Thigh L
	ThighLCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ThighLCapsule"));
	ThighLCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("thigh_L"));
	ThighLCapsule->SetRelativeLocationAndRotation(FVector(0.2, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ThighLCapsule->SetCapsuleRadius(0.1f);
	ThighLCapsule->SetCapsuleHalfHeight(0.3f);
	ThighLCapsule->SetCollisionProfileName(FName("FighterBody"));
	ThighLCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Thigh R
	ThighRCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ThighRCapsule"));
	ThighRCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("thigh_R"));
	ThighRCapsule->SetRelativeLocationAndRotation(FVector(0.2, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ThighRCapsule->SetCapsuleRadius(0.1f);
	ThighRCapsule->SetCapsuleHalfHeight(0.3f);
	ThighRCapsule->SetCollisionProfileName(FName("FighterBody"));
	ThighRCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Shin L
	ShinLCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ShinLCapsule"));
	ShinLCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("shin_L"));
	ShinLCapsule->SetRelativeLocationAndRotation(FVector(0.2, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ShinLCapsule->SetCapsuleRadius(0.075f);
	ShinLCapsule->SetCapsuleHalfHeight(0.2f);
	ShinLCapsule->SetCollisionProfileName(FName("FighterBody"));
	ShinLCapsule->ShapeColor = FColor(0, 0, 255, 255);

	// Shin R
	ShinRCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ShinRCapsule"));
	ShinRCapsule->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("shin_R"));
	ShinRCapsule->SetRelativeLocationAndRotation(FVector(0.2, 0.0, 0.0), FRotator(-90.0, 0.0, 0.0));
	ShinRCapsule->SetCapsuleRadius(0.075f);
	ShinRCapsule->SetCapsuleHalfHeight(0.2f);
	ShinRCapsule->SetCollisionProfileName(FName("FighterBody"));
	ShinRCapsule->ShapeColor = FColor(0, 0, 255, 255);

	HipsEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HipsEmitter"));
	HipsEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hips"));

	HeadEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HeadEmitter"));
	HeadEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("head"));

	UpperArmLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UpperArmLEmitter"));
	UpperArmLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("upper_arm_L"));

	UpperArmREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UpperArmREmitter"));
	UpperArmREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("upper_arm_R"));

	ForearmLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ForearmLEmitter"));
	ForearmLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("forearm_L"));

	ForearmREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ForearmREmitter"));
	ForearmREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("forearm_R"));

	HandLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HandLEmitter"));
	HandLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_L"));

	HandREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("HandREmitter"));
	HandREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_R"));

	ThighLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThighLEmitter"));
	ThighLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("thigh_L"));

	ThighREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ThighREmitter"));
	ThighREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("thigh_R"));

	ShinLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ShinLEmitter"));
	ShinLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("shin_L"));

	ShinREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ShinREmitter"));
	ShinREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("shin_R"));

	FootLEmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FootLEmitter"));
	FootLEmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("foot_L"));

	FootREmitter = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FootREmitter"));
	FootREmitter->AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("foot_R"));
}

// Called when the game starts or when spawned
void AFighterPawn::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	GameMode = Cast<AFightingGameMode>(World->GetAuthGameMode());

	// Set initial state
	CurrentState = EFighterState::GroundNeutral;

	if (!InnateAsset) {
		UE_LOG(LogTemp, Error, TEXT("No InnateAsset was set."));
		return;
	}

	HipsEmitter->Deactivate();
	HeadEmitter->Deactivate();
	UpperArmLEmitter->Deactivate();
	UpperArmREmitter->Deactivate();
	ForearmLEmitter->Deactivate();
	ForearmREmitter->Deactivate();
	HandLEmitter->Deactivate();
	HandREmitter->Deactivate();
	ThighLEmitter->Deactivate();
	ThighREmitter->Deactivate();
	ShinLEmitter->Deactivate();
	ShinREmitter->Deactivate();
	FootLEmitter->Deactivate();
	FootREmitter->Deactivate();
}

void AFighterPawn::EnterState(EFighterState State)
{
	if (State == CurrentState) {
		return;
	}

	OnEnterState(State, CurrentState);

	// End Shift
	if (CurrentAttack) {
		FVector Location = GetActorLocation();
		FVector Destination =
			Location
			+ FVector(
				CurrentAttack->ShiftEnd.X * GetActorForwardVector().X,
				0.0f,
				CurrentAttack->ShiftEnd.Y);
		SetActorLocation(Destination);
	}

	CurrentState = State;
	CurrentAttack = nullptr;
	CurrentFrame = 0.0f;
}

void AFighterPawn::EnterNormalAttackState(EFighterState State)
{
	UFighterAttackAsset* AttackAsset = nullptr;

	switch (State) {
	case EFighterState::GroundNeutral:
		AttackAsset = InnateAsset->GroundNeutralAttack;
		break;
	case EFighterState::GroundForward:
		AttackAsset = InnateAsset->GroundForwardAttack;
		break;
	case EFighterState::GroundCrouching:
		AttackAsset = InnateAsset->GroundCrouchingAttack;
		break;
	case EFighterState::AirNeutral:
		AttackAsset = InnateAsset->AirNeutralAttack;
		break;
	case EFighterState::AirForward:
		AttackAsset = InnateAsset->AirForwardAttack;
		break;
	case EFighterState::AirCrouching:
		AttackAsset = InnateAsset->AirCrouchingAttack;
		break;
	default:
		return;
	}

	EnterNormalAttackState(AttackAsset);
}

void AFighterPawn::EnterNormalAttackState(UFighterAttackAsset* AttackAsset)
{
	OnEnterNormalAttackState(AttackAsset, CurrentState, CurrentFrame * 60.0f);

	EnterState(EFighterState::Attack);
	CurrentAttack = AttackAsset;

	bHasAttackHit = false;

	// Start Shift
	FVector Location = GetActorLocation();
	FVector Destination =
		Location
		+ FVector(
			AttackAsset->ShiftStart.X * GetActorForwardVector().X,
			0.0f,
			AttackAsset->ShiftStart.Y);
	SetActorLocation(Destination);

	// Initial velocity
	Velocity += CurrentAttack->VelocityInitial;

	// Gain resource
	Resource = FMathf::Clamp(
		Resource + AttackAsset->ResourceGain * GameMode->ResourceMultiplier,
		0.0f,
		ResourceMax);
	if (AttackAsset->ResourceGain > 0.0f)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Resource: %f"), Resource));
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update timers
	CurrentFrame += DeltaTime * 60.0f;
	JumpInputTime -= DeltaTime;
	EvadeInputTime -= DeltaTime;
	NormalInputTime -= DeltaTime;
	SpecialInputTime -= DeltaTime;

	// Set attack activity
	if (CurrentState == EFighterState::Attack) {
		if (CurrentFrame >= CurrentAttack->StartupFrames
			&& CurrentFrame < CurrentAttack->StartupFrames + CurrentAttack->ActiveFrames
			&& !bHasAttackHit) {
			//GEngine->AddOnScreenDebugMessage(
			//	-1,
			//	5.0f,
			//	FColor::Purple,
			//	FString::Printf(TEXT("Active Frame: %f"), CurrentFrame - CurrentAttack->StartupFrames));
			
			// Get hit location and, if necessary, AttackStartLocation
			FVector HitLocation = SkeletalMesh->GetSocketLocation(CurrentAttack->SocketName);
			if (!bIsAttackActive)
				AttackStartLocation = HitLocation;
			
			// Mark that the attack has begun
			bIsAttackActive = true;

			// Emit particles
			HeadEmitter->SetWorldLocation(HitLocation);
			HeadEmitter->Activate();

			// Check hit
			FHitResult Hit;
			bHasAttackHit = UKismetSystemLibrary::SphereTraceSingleByProfile(
				GetWorld(),
				AttackStartLocation,
				HitLocation,
				CurrentAttack->Radius,
				"FighterAttack",
				false,
				{ this },
				EDrawDebugTrace::ForDuration,
				Hit,
				true,
				FLinearColor::Red,
				FLinearColor::Green,
				0.25f
			);

			// Check for opponent and hit
			if (bHasAttackHit) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HIT")));
				AFighterPawn* Target = Cast<AFighterPawn>(Hit.GetActor());
				//if (Target)
				//	Target->TakeHit(this, 1.0f);
			}
		}
		else if (bIsAttackActive) {
			// Mark that the attack has ended
			bIsAttackActive = false;

			// Stop emitting particles
			HeadEmitter->Deactivate();

			GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				FColor::Purple,
				FString::Printf(TEXT("Active Frame End")));
		}
	}

	// Find movement properties
	FVector2D VelocityTarget;
	FVector2D Acceleration;
	FVector2D Deceleration;
	bool InGroundState = CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::GroundCrouching;
	bool InAirState = CurrentState == EFighterState::AirNeutral
		|| CurrentState == EFighterState::AirForward
		|| CurrentState == EFighterState::AirCrouching;
	bool InNeutralState = CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::AirNeutral;
	bool InForwardState = CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::AirForward;
	bool InCrouchingState = CurrentState == EFighterState::GroundCrouching
		|| CurrentState == EFighterState::AirCrouching;
	bool InAttack = CurrentState == EFighterState::Attack;

	// Calculate momentum
	// Not attacking
	if (!InAttack) {
		// On the ground
		if (InGroundState) {
			VelocityTarget = {
				InCrouchingState ? 0.0 : MovementInput * InnateAsset->GroundSpeed,
				0.0
			};
			Acceleration = {
				InnateAsset->GroundAcceleration,
				0.0
			};
			Deceleration = {
				InnateAsset->GroundDeceleration,
				0.0
			};
		}
		// In the air
		else {
			VelocityTarget = {
				InCrouchingState ? 0.0 : MovementInput * InnateAsset->AirSpeed,
				InnateAsset->FallVelocity
			};
			Acceleration = {
				InnateAsset->AirAcceleration,
				0.0
			};
			Deceleration = {
				InnateAsset->AirDeceleration,
				(Velocity.Y > 0.0 ? InnateAsset->GravityUp : InnateAsset->GravityDown) * (InCrouchingState ? InnateAsset->FastFall : 1.0)
			};
		}
	}
	// Attacking
	else {
		VelocityTarget = CurrentAttack->VelocityTarget;
		Acceleration = CurrentAttack->Acceleration;
		Deceleration = CurrentAttack->Deceleration;
	}

	// Calculate horizontal velocity
	if (Velocity.X <= VelocityTarget.X - Acceleration.X * DeltaTime) {
		Velocity.X += Acceleration.X * DeltaTime;
	}
	else if (Velocity.X >= VelocityTarget.X + Deceleration.X * DeltaTime) {
		Velocity.X -= Deceleration.X * DeltaTime;
	}
	else {
		Velocity.X = VelocityTarget.X;
	}

	// Calculate vertical velocity
	if (Velocity.Y <= VelocityTarget.Y - Acceleration.Y * DeltaTime) {
		Velocity.Y += Acceleration.Y * DeltaTime;
	}
	else if (Velocity.Y >= VelocityTarget.Y + Deceleration.Y * DeltaTime) {
		Velocity.Y -= Deceleration.Y * DeltaTime;
	}
	else {
		Velocity.Y = VelocityTarget.Y;
	}


	// Calculate destination
	FVector Location = GetActorLocation();
	bool bIsTouchingGround = Location.Z <= 0.0f;
	bool bTouchedGroundThisFrame = false;
	FVector Destination = Location + FVector(Velocity.X * GetActorForwardVector().X, 0.0f, Velocity.Y);
	if (!bIsTouchingGround && Destination.Z <= 0.0) {
		bTouchedGroundThisFrame = true;
	}
	bIsTouchingGround = Destination.Z <= 0.0;
	if (bIsTouchingGround) {
		Destination.Z = 0.0;
		Velocity.Y = 0.0;
	}

	// Translate
	SetActorLocation(Destination);

	// Landing
	if (bTouchedGroundThisFrame)
	{
		EnterState(EFighterState::GroundNeutral);
	}
	// Attacking (Normal)
	else if (NormalInputTime > 0.0f)
	{
		NormalInputTime = 0.0f;
		EnterNormalAttackState(CurrentState);
	}
	// Jumping
	else if ((CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::GroundCrouching)
		&& bIsTouchingGround
		&& JumpInputTime > 0.0f)
	{
		JumpInputTime = 0.0f;
		Velocity += { 0.0, InnateAsset->JumpVelocity };
		EnterState(EFighterState::AirNeutral);
	}
	// Crouching (Ground)
	else if ((CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::GroundCrouching)
		&& CrouchInput > 0.0f)
	{
		EnterState(EFighterState::GroundCrouching);
	}
	// Moving (Ground)
	else if ((CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::GroundCrouching)
		&& MovementInput != 0.0f
		&& CrouchInput == 0.0f)
	{
		if (MovementInput < 0.0f) {
			TurnAround();
		}
		EnterState(EFighterState::GroundForward);
	}
	// Stopping (Ground)
	else if ((CurrentState == EFighterState::GroundNeutral
		|| CurrentState == EFighterState::GroundForward
		|| CurrentState == EFighterState::GroundCrouching)
		&& MovementInput == 0.0f)
	{
		EnterState(EFighterState::GroundNeutral);
	}
	// Crouching (Air)
	else if ((CurrentState == EFighterState::AirNeutral
		|| CurrentState == EFighterState::AirForward
		|| CurrentState == EFighterState::AirCrouching)
		&& CrouchInput> 0.0f)
	{
		EnterState(EFighterState::AirCrouching);
	}
	// Moving (Air)
	else if ((CurrentState == EFighterState::AirNeutral
		|| CurrentState == EFighterState::AirForward)
		&& MovementInput != 0.0f
		&& CrouchInput == 0.0f)
	{
		if (MovementInput < 0.0f) {
			TurnAround();
		}
		EnterState(EFighterState::AirForward);
	}
	// Stopping (Air)
	else if ((CurrentState == EFighterState::AirNeutral
		|| CurrentState == EFighterState::AirForward
		|| CurrentState == EFighterState::AirCrouching)
		&& MovementInput == 0.0f)
	{
		EnterState(EFighterState::AirNeutral);
	}
	// Ending
	else if (CurrentAttack
		&& CurrentFrame >= CurrentAttack->StartupFrames
			+ CurrentAttack->ActiveFrames
			+ CurrentAttack->RecoveryFrames)
	{
		EnterState(CurrentAttack->End);
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
	UFighterAttackAsset* CanceledAttack = CurrentAttack;

	if (CanceledAttack)
		OnHardCancel(CanceledAttack, CanceledVelocity);

	ResetToNeutral();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("HARD CANCEL!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, FString::Printf(TEXT("Resource: %f"), Resource));
}

void AFighterPawn::TurnAround()
{
	bIsFacingRight = !bIsFacingRight;

	Velocity.X *= -1.0f;

	if (bIsFacingRight) {
		SetActorRelativeRotation(FRotator(0.0, 0.0, 0.0));
	}
	else {
		SetActorRelativeRotation(FRotator(0.0, 180.0, 0.0));
	}
}

void AFighterPawn::ResetToNeutral()
{
	FVector Location = GetActorLocation();
	bool bTouchingGround = Location.Z <= 0.0;

	Velocity = { 0.0f, 0.0f };
	if (bTouchingGround) {
		EnterState(EFighterState::GroundNeutral);
	}
	else {
		EnterState(EFighterState::AirNeutral);
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

float AFighterPawn::GetCurrentFrame()
{
	return CurrentFrame;
}

EFighterState AFighterPawn::GetCurrentState()
{
	return CurrentState;
}

UFighterAttackAsset* AFighterPawn::GetCurrentAttack()
{
	return CurrentAttack;
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
	if (CurrentState != EFighterState::Attack) {
		return nullptr;
	}

	UAnimSequence* AttackAnimation = nullptr;

	// Current attack state is leading in
	if (CurrentFrame < CurrentAttack->StartupFrames) {
		AttackAnimation = CurrentAttack->AnimationLead;
	}
	// Current attack state is following through
	else {
		AttackAnimation = CurrentAttack->AnimationFollow;
	}

	return AttackAnimation;
}

float AFighterPawn::GetAnimationPlayRate()
{
	if (CurrentState != EFighterState::Attack) {
		return 1.0f;
	}

	float PlayRate = 1.0f;

	// Current attack state is leading in
	if (CurrentFrame < CurrentAttack->StartupFrames) {
		PlayRate = 60.0f / (float)(CurrentAttack->StartupFrames);
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, FString::Printf(TEXT("Lead-in: %f"), PlayRate));
	}
	// Current attack state is following through
	else {
		PlayRate = 60.0f / (float)(CurrentAttack->ActiveFrames + CurrentAttack->RecoveryFrames);
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, FString::Printf(TEXT("Follow-through: %f"), PlayRate));
	}

	return PlayRate;
}
