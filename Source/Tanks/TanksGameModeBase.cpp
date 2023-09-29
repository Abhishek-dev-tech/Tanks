// Copyright Epic Games, Inc. All Rights Reserved.


#include "TanksGameModeBase.h"
#include "PlayerTank.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

void ATanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();

   playerTank =  Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

   StartGame();
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
    }
}