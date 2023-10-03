// Copyright Epic Games, Inc. All Rights Reserved.


#include "TanksGameModeBase.h"
#include "PlayerTank.h"
#include "EnemyBase.h"
#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

void ATanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();

   playerTank =  Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

   StartGame();

   score = 0;
}

void ATanksGameModeBase::ActorDied(AActor* actor)
{
    if(actor == playerTank)
    {
        playerTank->HandleActorDied();
        playerTank->DisableInput(playerTank->GetTankPlayerController());
        playerTank->GetTankPlayerController()->bShowMouseCursor = false;
    }
    else if(AEnemyBase* enemy = Cast<AEnemyBase>(actor))
    {
        enemy->HandleActorDied();
        enemySpawner->enemyCount --;
        score += 100;
    }
}

FString ATanksGameModeBase::GetScore() const
{
    return FString::Printf(TEXT("Score: %d"), score);
}

void ATanksGameModeBase::SetEnemySpawner(AEnemySpawner *_enemySpawner)
{
    enemySpawner = _enemySpawner;
}