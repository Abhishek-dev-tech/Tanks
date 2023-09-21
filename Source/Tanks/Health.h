// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float maxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float health;

	class ATanksGameModeBase *tankGameMode;

	UFUNCTION()
	void TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* damageCauser);
};
