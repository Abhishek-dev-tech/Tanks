// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PlayerTank.h"
#include "TimerManager.h"

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &AEnemyTank::Fire, fireRate, true);
}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector target = playerTank->GetActorLocation();

	Move(target, DeltaTime);
}

void AEnemyTank::Move(const FVector target, float deltaTime)
{
	RotateTurret(playerTank->GetActorLocation(), deltaTime);

	if (TargetInRange(followDistance))
		return;
	
	FVector direction = target - GetActorLocation();
	direction.Normalize();

	FVector deltaLocation = GetActorLocation() + direction * speed * deltaTime;

	SetActorLocation(deltaLocation);

	Rotate(target, deltaTime);
}

void AEnemyTank::Rotate(const FVector target, float deltaTime)
{
	FVector direction = target - GetActorLocation();
	direction.Normalize();

	FRotator deltaRotation = direction.Rotation();

	deltaRotation.Roll = 0;
	deltaRotation.Pitch = 0;

	SetActorRotation(FMath::RInterpTo(
		GetActorRotation(),
		deltaRotation,
		deltaTime,
		20.f
	));
}

void AEnemyTank::Fire()
{
	if (TargetInRange(followDistance) && !playerTank->playerDead)
	{
		Super::Fire();
	}
}