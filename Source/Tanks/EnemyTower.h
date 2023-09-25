// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "EnemyBase.h"
#include "EnemyTower.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API AEnemyTower : public AEnemyBase
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
