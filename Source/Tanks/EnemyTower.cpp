// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "PlayerTank.h"
#include "TimerManager.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(fireTimerHandle, this, &AEnemyTower::Fire, fireRate, true);
}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetInRange(attackDistance))
		RotateTurret(playerTank->GetActorLocation(), DeltaTime);
	
}

void AEnemyTower::Fire()
{
	if (TargetInRange(attackDistance) && !playerTank->playerDead)
	{
		Super::Fire();
	}
}

