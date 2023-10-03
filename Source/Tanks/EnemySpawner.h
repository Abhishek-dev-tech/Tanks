// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class TANKS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	float enemyCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float maxEnemies;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float enemySpawnDelay;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float spawnDistanceFromPlayer;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AEnemyTank> enemyTank;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AEnemyTower> enemyTower;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* spawnParticle;

	class APlayerTank *playerTank;

	FTimerHandle spawnTimerHandle;

	UFUNCTION()
	void SpawnEnemies();

	FVector GetSpawnLocation();

};
