// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraShake.h"
#include "SWeapon.generated.h"

UCLASS()
class COOPGAME_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components")
		USkeletalMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category="Weapon")
		TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* MuzzleEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* DefaultImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* FleshImpactEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		UParticleSystem* TracerEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName MuzzleSocketName;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<UCameraShake> FireCamShake;
	float BaseDamage;
	virtual void PlayFireEffects(FVector TracerEndPoint);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Fire();

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;
	/*RPM - Bullets per minute fired by weapon*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		float RateOfFire;
	//Derived from RPM
	float TimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		USoundBase* SoundOfFire;
public:

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void StartFire();
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void StopFire();
	UFUNCTION(BlueprintCallable)
		FTransform GetMuzzleTransform() const;
};
