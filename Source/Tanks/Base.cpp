// Fill out your copyright notice in the Description page of Project Settings.


#include "Base.h"
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABase::ABase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Copmonent"));
	RootComponent = boxComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(boxComponent);

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

	SetScaleSmoothly(FVector(1, 1, 1), DeltaTime);
}

void ABase::RotateTurret(const FVector target, float deltaTime)
{
	FVector direction = target - turretMesh->GetComponentLocation();

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
	turretMesh->SetWorldScale3D(FVector(1.25f, 1.25f, 1.f));

	AProjectile *tempProjectile = GetWorld()->SpawnActor<AProjectile>(projectile, projectileSpawnPoint->GetComponentLocation(), projectileSpawnPoint->GetComponentRotation());

	tempProjectile->SetOwner(this);
}

void ABase::SetScaleSmoothly(FVector value, float deltaTime)
{
	turretMesh->SetWorldScale3D(FMath::VInterpTo(
		turretMesh->GetComponentScale(),
		value,
		deltaTime,
		10.f
	));
}

void ABase::HandleActorDied()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, deathParticle, GetActorLocation(), GetActorRotation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShake);
}