// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyBase : public ABase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void HandleActorDied();

	void Fire();

protected:
	virtual void BeginPlay() override;

	bool TargetInRange(float value);

	class APlayerTank* playerTank;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float attackDistance;

private:

	UPROPERTY(EditAnywhere, Category = "Combat")
	float fireRate = 2.5f;

	FTimerHandle fireTimerHandle;
};
