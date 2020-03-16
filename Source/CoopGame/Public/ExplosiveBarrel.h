// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class COOPGAME_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UMaterialInterface* BlownUpMaterial;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UParticleSystem* ParticleSystem;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class URadialForceComponent* RadialForce;
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class USHealthComponent* HealthComponent;
	bool iSBlownUp;

	UPROPERTY(EditDefaultsOnly)
		float ExplosionImpulse;
	UFUNCTION()
		void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta,
			const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
};
