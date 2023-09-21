// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	playerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBase::HandleActorDied()
{
	Super::HandleActorDied();
	Destroy();
}

bool AEnemyBase::TargetInRange(float value)
{
	if (FVector::Dist(playerTank->GetActorLocation(), GetActorLocation()) < value)
		return true;

	return false;
	
}