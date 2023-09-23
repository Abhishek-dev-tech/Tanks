// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Base.generated.h"

class UBoxComponent;

UCLASS()
class TANKS_API ABase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABase();

	UFUNCTION()
	void HandleActorDied();

protected:

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AProjectile> projectile;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void RotateTurret(const FVector target, float deltaTime);

	UFUNCTION()
	void Fire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* boxComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* turretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* projectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* deathParticle;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> deathCameraShake;

	UFUNCTION()
	void SetScaleSmoothly(FVector value, float deltaTime);
};