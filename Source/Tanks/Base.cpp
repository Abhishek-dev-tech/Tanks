// Fill out your copyright notice in the Description page of Project Settings.


#include "Base.h"
#include "Projectile.h"

// Sets default values
ABase::ABase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = baseMesh;

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	projectileSpawnPoint->SetupAttachment(turretMesh);
}

// Called when the game starts or when spawned
void ABase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase::RotateTurret(const FVector target, float deltaTime)
{
	FVector direction = target - turretMesh->GetComponentLocation();
	//direction.Normalize();

	FRotator deltaRotation = direction.Rotation();

	deltaRotation.Roll = 0;
	deltaRotation.Pitch = 0;

	turretMesh->SetWorldRotation(FMath::RInterpTo(
		turretMesh->GetComponentRotation(),
		deltaRotation,
		deltaTime,
		15.f
	));
}

void ABase::Fire()
{
	AProjectile *tempProjectile = GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnPoint->GetComponentLocation(), projectileSpawnPoint->GetComponentRotation());

	tempProjectile->SetOwner(this);
}