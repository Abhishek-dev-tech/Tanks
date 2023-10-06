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

	UFUNCTION(BlueprintCallable)
	void Playing();

	bool IsGameStarted() { return isGameStarted; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void StartPlaying();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

private:

	class APlayerTank *playerTank;

	int score;

	bool isGameStarted;
};
