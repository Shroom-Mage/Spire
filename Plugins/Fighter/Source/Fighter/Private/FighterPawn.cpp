// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "FightingGameMode.h"
#include "FighterStateAsset.h"
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
	BodyBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BodyBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BodyBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
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

void AFighterPawn::EnterState(UFighterStateAsset* State, EVelocityType VelocityType, bool bResetAnimation, bool bSplit)
{
	if (State == CurrentState || State == nullptr)
		return;

	UFighterStateAsset* PreviousState = CurrentState;
	CurrentState = State;

	// Play animation
	if (State->Animation != CurrentAnimation || bResetAnimation) {
		CurrentAnimation = State->Animation;
		SkeletalMesh->PlayAnimation(State->Animation, State->bLoopAnimation);
	}

	// Adjust body box
	FVector BodyBoxLocation = FVector(State->BodyBoxLocation.X, 0.0f, State->BodyBoxLocation.Y);
	FVector BodyBoxExtent = FVector(State->BodyBoxExtent.X, 0.0f, State->BodyBoxExtent.Y);
	BodyBox->SetRelativeLocation(BodyBoxLocation);
	BodyBox->SetBoxExtent(BodyBoxExtent);

	// Adjust attack box
	FVector AttackBoxLocation = FVector(State->AttackBoxLocation.X, 0.0f, State->AttackBoxLocation.Y);
	FVector AttackBoxExtent = FVector(State->AttackBoxExtent.X, 0.0f, State->AttackBoxExtent.Y);
	AttackBox->SetRelativeLocation(AttackBoxLocation);
	AttackBox->SetBoxExtent(AttackBoxExtent);
	bHasAttackHit = false;

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
	if (StateTime > CurrentState->ActiveStartTime && StateTime < CurrentState->ActiveEndTime && !bHasAttackHit) {
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
	if (CurrentState->CancelTime > 0.0f
		&& StateTime > CurrentState->CancelTime
		&& (MovementInput < 0.0f
			|| MovementInput > 0.0f
			|| JumpInputTime > 0.0f
			|| EvadeInputTime > 0.0f
			|| NormalInputTime > 0.0f
			|| SpecialInputTime > 0.0f))
	{
		if (bTouchedGround)
			CurrentState = StandingNeutral;
		else
			CurrentState = AirNeutral;
	}

	// Enter this state's normal attack if attempting to attack
	if (NormalInputTime > 0.0f
		&& CurrentState->AttackNormal)
	{
		NormalInputTime = 0.0f;
		EnterState(CurrentState->AttackNormal, EVelocityType::ADD, true);
	}
	// Enter Air state if attempting to jump while touching the ground
	if ((CurrentState == StandingNeutral
		|| CurrentState == StandingForward
		|| CurrentState == StandingBackward)
		&& bTouchedGround
		&& JumpInputTime > 0.0f
		&& AirNeutral)
	{
		JumpInputTime = 0.0f;
		EnterState(AirNeutral, EVelocityType::ADD);
		return;
	}
	// Enter Landing state if the ground is touched from the air
	if ((CurrentState == AirNeutral
		|| CurrentState == AirForward
		|| CurrentState == AirBackward)
		&& bTouchedGround
		&& StandingNeutral)
	{
		EnterState(StandingNeutral, EVelocityType::ADD);
		return;
	}
	// Enter StandingForward state if attempting to move while standing
	if ((CurrentState == StandingNeutral
		|| CurrentState == StandingForward
		|| CurrentState == StandingBackward)
		&& MovementInput > 0.0f
		&& StandingForward)
	{
		EnterState(StandingForward, EVelocityType::IGNORE);
		return;
	}
	// Enter StandingBackward state if attempting to move while standing
	if ((CurrentState == StandingNeutral
		|| CurrentState == StandingForward
		|| CurrentState == StandingBackward)
		&& MovementInput < 0.0f
		&& StandingBackward)
	{
		EnterState(StandingBackward, EVelocityType::IGNORE);
		return;
	}
	// Enter StandingNeutral state if not attempting to move while standing
	if ((CurrentState == StandingNeutral
		|| CurrentState == StandingForward
		|| CurrentState == StandingBackward)
		&& MovementInput == 0.0f
		&& StandingNeutral)
	{
		EnterState(StandingNeutral, EVelocityType::IGNORE);
		return;
	}
	// Enter AirForward state if attempting to move while Air
	if ((CurrentState == AirNeutral
		|| CurrentState == AirBackward)
		&& MovementInput > 0.0f
		&& AirForward)
	{
		EnterState(AirForward, EVelocityType::IGNORE);
		return;
	}
	// Enter AirBackward state if attempting to move while Air
	if ((CurrentState == AirNeutral
		|| CurrentState == AirForward)
		&& MovementInput < 0.0f
		&& AirBackward)
	{
		EnterState(AirBackward, EVelocityType::IGNORE);
		return;
	}
	// Enter AirNeutral state if not attempting to move while Air
	if ((CurrentState == AirForward
		|| CurrentState == AirBackward)
		&& MovementInput == 0.0f
		&& AirNeutral)
	{
		EnterState(AirNeutral, EVelocityType::IGNORE);
		return;
	}
	// Enter End state if Duration was reached
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Pawn OverlapBegin")));
	if (OtherComp->GetFName() == TEXT("BodyBox")) {
		AFighterPawn* OtherFighter = Cast<AFighterPawn>(OtherActor);
		if (OtherFighter != this)
			Target = OtherFighter;
	}
}

void AFighterPawn::OnAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, FString::Printf(TEXT("Pawn OverlapEnd")));
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
		EnterState(StandingNeutral, EVelocityType::IGNORE, true);
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

bool AFighterPawn::GetIsFacingRight()
{
	return bIsFacingRight;
}

void AFighterPawn::TakeHit(AFighterPawn* Attacker, float Damage)
{
	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("HIT!"));
	// Increment the score
	if (GameMode) {
		GameMode->AddPoint(Attacker);
	}
}
