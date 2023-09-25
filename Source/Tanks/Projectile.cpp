// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = projectileMesh;

	pointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	pointLight->SetupAttachment(projectileMesh);

	projectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	projectileTrail->SetupAttachment(pointLight);

	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	projectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent *hitComp, AActor *otherActor, UPrimitiveComponent *otherComp, FVector normalImpluse, const FHitResult &hitResult)
{
	AActor *owner = GetOwner();

	if(owner == nullptr && otherActor == this && otherActor == owner)
	{
		Destroy();
		return;
	}

	AController *instigatorController = owner->GetInstigatorController();

	if(otherActor->ActorHasTag("Enemy") || otherActor->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(otherActor,
		damageAmount,
		instigatorController,
		this,
		UDamageType::StaticClass());
	}

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShake);

	UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetActorLocation(), GetActorRotation());
	Destroy();
}

