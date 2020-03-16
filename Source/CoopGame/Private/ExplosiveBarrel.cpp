// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SHealthComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForce"));
	RadialForce->Radius = 250;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->bIgnoreOwningActor = true;
	RadialForce->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<USHealthComponent>(TEXT("Health"));
	HealthComponent->OnHealthChanged.AddDynamic(this, &AExplosiveBarrel::OnHealthChanged);
	iSBlownUp = false;

	ExplosionImpulse = 400;
}

void AExplosiveBarrel::OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health==0.f && !iSBlownUp)
	{
		iSBlownUp = true;
		const FVector BustIntensity = ExplosionImpulse * FVector::UpVector;
		MeshComponent->AddImpulse(BustIntensity, NAME_None, true);
		RadialForce->FireImpulse();
		if (BlownUpMaterial)
			MeshComponent->SetMaterial(0, BlownUpMaterial);
		if (ParticleSystem)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorTransform());
	}
}

