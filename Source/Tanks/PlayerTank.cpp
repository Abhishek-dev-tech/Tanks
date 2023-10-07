// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TanksGameModeBase.h"

// Sets default values
APlayerTank::APlayerTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void APlayerTank::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController *_playerController = Cast<APlayerController>(Controller);

	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_playerController->GetLocalPlayer());

	subSystem->AddMappingContext(playerMappingContext, 0);

	tankPlayerController = _playerController;

	tankGameMode = Cast<ATanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void APlayerTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!tankPlayerController)
		return;
	
	FHitResult hitResult;
	tankPlayerController->GetHitResultUnderCursor(
		ECollisionChannel::ECC_Visibility,
		false,
		hitResult
	);

	if(!tankGameMode->IsGameStarted())
		return;

	DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 5, 8, FColor::Black, false, -1.f);
	RotateTurret(hitResult.ImpactPoint, DeltaTime);

	SetCamera();
}

// Called to bind functionality to input
void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerTank::Move);
	EnhancedInputComponent->BindAction(fireAction, ETriggerEvent::Started, this, &APlayerTank::Fire);


	EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Completed, this, &APlayerTank::ResetInputValues);
}

void APlayerTank::Move(const FInputActionValue &value)
{	
	moveVector = FMath::VInterpTo(
		moveVector,
		value.Get<FVector>(),
		UGameplayStatics::GetWorldDeltaSeconds(this),
		2.5f);

	AddActorLocalOffset(FVector(moveVector.Y, 0, 0) * speed * UGameplayStatics::GetWorldDeltaSeconds(this), true);

	Rotate();
}

void APlayerTank::Rotate()
{
	FRotator deltaRotation = FRotator::ZeroRotator;

	deltaRotation.Yaw = moveVector.X * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

	AddActorLocalRotation(deltaRotation);
}

void APlayerTank::ResetInputValues(const FInputActionValue &value)
{
	moveVector = FVector::ZeroVector;
}

void APlayerTank::HandleActorDied()
{
	Super::HandleActorDied();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	playerDead = true;
}

void APlayerTank::SetCamera()
{
	FVector targetLocation(0, 0, 15.f);
	FRotator targetRotation(-30, 0, 0);

	springArm->SetRelativeLocation(FMath::VInterpTo(
		springArm->GetRelativeLocation(),
		targetLocation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		7.5f
	));
	
	springArm->SetRelativeRotation(FMath::RInterpTo(
		springArm->GetRelativeRotation(),
		targetRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		7.5f
	));

	springArm->TargetArmLength = 2500;
}