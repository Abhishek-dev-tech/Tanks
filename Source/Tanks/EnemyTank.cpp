// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTank.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AEnemyTank::BeginPlay()
{
	Super::BeginPlay();
	
    playerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	
}

void AEnemyTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Move(playerTank->GetActorLocation(), DeltaTime);
}

void AEnemyTank::Move(const FVector target, float deltaTime)
{
    RotateTurret(target, deltaTime);

    if(FVector::Dist(target, GetActorLocation()) < distance)
	{
		inRange = true;
		return;
	}

	inRange = false;

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