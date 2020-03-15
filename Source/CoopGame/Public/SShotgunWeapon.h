// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SShotgunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ASShotgunWeapon : public ASWeapon
{
	GENERATED_BODY()
public:
	ASShotgunWeapon();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		int32 BulletsInOneFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = 0, ClampMax = 90))
		float XMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = -90, ClampMax = 0))
		float XMin;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = 0, ClampMax = 90))
		float YMax;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = -90, ClampMax = 0))
		float YMin;
	void Fire() override;
	void PlayFireEffects(TArray<FVector>& TracerEndPoint);
	FRandomStream Rand;
};
