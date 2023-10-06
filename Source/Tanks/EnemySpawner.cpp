// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "EnemyTower.h"
#include "TanksGameModeBase.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &AEnemySpawner::SpawnEnemies, enemySpawnDelay, true);

	playerTank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	tankGameMode = Cast<ATanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemies()
{
	if(playerTank->playerDead || !tankGameMode->IsGameStarted())
		return;

	enemyCount++;

	FVector randSpawnLocation = GetSpawnLocation();

	UGameplayStatics::SpawnEmitterAtLocation(this, spawnParticle, randSpawnLocation, GetActorRotation());

	if(FMath::RandBool())
		GetWorld()->SpawnActor<AEnemyTank>(enemyTank, randSpawnLocation, FRotator::ZeroRotator);
	else
		GetWorld()->SpawnActor<AEnemyTower>(enemyTower, randSpawnLocation, FRotator::ZeroRotator);
}

FVector AEnemySpawner::GetSpawnLocation()
{
	if(!playerTank)
		return FVector(0, 0, 0);

	FVector spawnLocation;
	FVector playerLocation = playerTank->GetActorLocation();

	int32 randX = FMath::RandRange(playerLocation.X - spawnDistanceFromPlayer, playerLocation.X + spawnDistanceFromPlayer);
	int32 randY = FMath::RandRange(playerLocation.Y - spawnDistanceFromPlayer, playerLocation.Y + spawnDistanceFromPlayer);

	spawnLocation = FVector(randX, randY, playerLocation.Z);

	return spawnLocation;
}