// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void ActorDied(AActor* actor);

	UFUNCTION(BlueprintPure)
	FString GetScore() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

private:
	class AEnemySpawner *enemySpawner;

	class APlayerTank *playerTank;

	int score;

	UFUNCTION(BlueprintCallable)
	void SetEnemySpawner(AEnemySpawner *_enemySpawner);
};
