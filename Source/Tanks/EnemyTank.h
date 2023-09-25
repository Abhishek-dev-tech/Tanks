// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "EnemyBase.h"
#include "EnemyTank.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyTank : public AEnemyBase
{
	GENERATED_BODY()

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void Move(const FVector target, float deltaTime);

	UFUNCTION()
	void Rotate(const FVector target, float deltaTime);
};
