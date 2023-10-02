// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PlayerTank.h"
#include "TimerManager.h"

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector target = playerTank->GetActorLocation();

	Move(target, DeltaTime);
}

void AEnemyTank::Move(const FVector target, float deltaTime)
{
	if (!TargetInRange(followDistance) && !follow)
		return;

	follow = true;

	RotateTurret(playerTank->GetActorLocation(), deltaTime);

	if (TargetInRange(attackRange))
		return;
	
	FVector direction = target - GetActorLocation();
	direction.Normalize();

	FVector deltaLocation = GetActorLocation() + direction * speed * deltaTime;

	SetActorLocation(deltaLocation, true);

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
		10.f
	));
}