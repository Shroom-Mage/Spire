// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterPawn.h"
#include "FightingComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//#include "InputActionValue.h"

// Sets default values
AFighterPawn::AFighterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Fighting = CreateDefaultSubobject<UFightingComponent>(TEXT("Fighting"));

	Base = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	Base->SetupAttachment(RootComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Base);
	Fighting->SetSkeletalMesh(SkeletalMesh);

	BodyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBox"));
	BodyBox->SetupAttachment(Base);
	BodyBox->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	BodyBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BodyBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BodyBox->ShapeColor = FColor(0, 0, 255, 255);
	Fighting->SetBodyBox(BodyBox);

	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	AttackBox->SetupAttachment(Base);
	AttackBox->ShapeColor = FColor(255, 0, 0, 255);
	Fighting->SetAttackBox(AttackBox);
	AttackBox->OnComponentBeginOverlap.AddDynamic(Fighting, &UFightingComponent::OnAttackOverlapBegin);
	AttackBox->OnComponentEndOverlap.AddDynamic(Fighting, &UFightingComponent::OnAttackOverlapEnd);

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
}

// Called every frame
void AFighterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFighterPawn::BeginMatch()
{
	OnBeginMatch();

	Fighting->BeginMatch();
}

void AFighterPawn::BeginRound()
{
	OnBeginRound();

	Fighting->BeginRound();
}

void AFighterPawn::BeginPoint()
{
	OnBeginPoint();

	Fighting->BeginPoint();
}

// Called to bind functionality to input
void AFighterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
	//	// Movement
	//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFighterPawn::Move);
	//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFighterPawn::Jump);
	//	EnhancedInputComponent->BindAction(EvadeAction, ETriggerEvent::Started, this, &AFighterPawn::Evade);

	//	// Attacks
	//	EnhancedInputComponent->BindAction(NormalAction, ETriggerEvent::Started, this, &AFighterPawn::Normal);
	//	EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Started, this, &AFighterPawn::Special);
	//}

	//if (PlayerInputComponent) {
	//	PlayerInputComponent->BindAxis("Move", this, &AFighterPawn::Move);
	//	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFighterPawn::Jump);
	//	PlayerInputComponent->BindAction("Evade", EInputEvent::IE_Pressed, this, &AFighterPawn::Evade);
	//	PlayerInputComponent->BindAction("Normal", EInputEvent::IE_Pressed, this, &AFighterPawn::Normal);
	//	PlayerInputComponent->BindAction("Special", EInputEvent::IE_Pressed, this, &AFighterPawn::Special);
	//}
}

UFightingComponent* AFighterPawn::GetFightingComponent()
{
	return Fighting;
}

//void AFighterPawn::Move(const FInputActionValue& Value)
//{
//	Fighting->Move(Value.Get<float>());
//}

void AFighterPawn::Move(float Value)
{
	Fighting->Move(bIsFacingRight ? Value : -Value);
}

void AFighterPawn::Jump()
{
	Fighting->Jump();
}

void AFighterPawn::Evade()
{
	Fighting->Evade();
}

void AFighterPawn::Normal()
{
	Fighting->Normal();
}

void AFighterPawn::Special()
{
	Fighting->Special();
}

UFighterStateAsset* AFighterPawn::HardCancel()
{
	UFighterStateAsset* CanceledState = Fighting->HardCancel();
	OnHardCancel(CanceledState);
	return CanceledState;
}

void AFighterPawn::TurnAround()
{
	bIsFacingRight = !bIsFacingRight;

	Fighting->TurnAround();

	if (bIsFacingRight) {
		SetActorRelativeRotation(FRotator(0.0, 0.0, 0.0));
		SpringArm->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
	}
	else {
		SetActorRelativeRotation(FRotator(0.0, 180.0, 0.0));
		SpringArm->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
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
