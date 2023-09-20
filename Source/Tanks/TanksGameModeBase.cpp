// Copyright Epic Games, Inc. All Rights Reserved.


#include "TanksGameModeBase.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Kismet/GameplayStatics.h"

void ATanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();

   playerTank =  Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATanksGameModeBase::ActorDied(AActor* actor)
{
    if(actor == playerTank)
    {
        playerTank->HandleActorDied();
        playerTank->DisableInput(playerTank->GetTankPlayerController());
        playerTank->GetTankPlayerController()->bShowMouseCursor = false;
    }
    else if(AEnemyTank* enemyTank = Cast<AEnemyTank>(actor))
    {
        enemyTank->HandleActorDied();
    }
}