// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base.h"
#include "InputActionValue.h"
#include "PlayerTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class TANKS_API APlayerTank : public ABase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	APlayerTank();

	void HandleActorDied();

	bool playerDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	APlayerController *GetTankPlayerController() const { return tankPlayerController; }

private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent *springArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent *camera;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext *playerMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction *moveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction *fireAction;

	UFUNCTION()
	void Move(const FInputActionValue &value);

	UFUNCTION()
	void Rotate();

	UFUNCTION()
	void ResetInputValues(const FInputActionValue &value);

	APlayerController *tankPlayerController;

	FVector moveVector;
};
