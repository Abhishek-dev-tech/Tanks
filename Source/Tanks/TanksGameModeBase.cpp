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

    playerTank->DisableInput(playerTank->GetTankPlayerController());

    isGameStarted = false;
}

void ATanksGameModeBase::ActorDied(AActor* actor)
{
    if(actor == playerTank)
    {
        playerTank->HandleActorDied();
        playerTank->DisableInput(playerTank->GetTankPlayerController());
        playerTank->GetTankPlayerController()->bShowMouseCursor = true;
        GameOver();
    }
    else if(AEnemyBase* enemy = Cast<AEnemyBase>(actor))
    {
        enemy->HandleActorDied();
        score += 100;
    }
}

FString ATanksGameModeBase::GetScore() const
{
    return FString::Printf(TEXT("Score: %d"), score);
}

void ATanksGameModeBase::Playing()
{
    StartPlaying();

    playerTank->EnableInput(playerTank->GetTankPlayerController());
    playerTank->GetTankPlayerController()->bShowMouseCursor = false;

    isGameStarted = true;
}