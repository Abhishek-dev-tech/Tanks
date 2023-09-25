// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"
#include "PlayerTank.h"
#include "TimerManager.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetInRange(attackDistance))
		RotateTurret(playerTank->GetActorLocation(), DeltaTime);
	
}

