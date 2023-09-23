// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "Health")
	float damageAmount;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent *projectileComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* hitParticle;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	class UParticleSystemComponent* projectileTrail;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> hitCameraShake;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *hitComp, AActor *otherActor, UPrimitiveComponent *otherComp, FVector normalImpluse, const FHitResult &hitResult);
};
