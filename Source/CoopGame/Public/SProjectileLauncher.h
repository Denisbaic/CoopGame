// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWeapon.h"
#include "SProjectileLauncher.generated.h"

/**
 * 
 */
UCLASS()
class COOPGAME_API ASProjectileLauncher : public ASWeapon
{
	GENERATED_BODY()

public:
	ASProjectileLauncher();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
		TSubclassOf<AActor> ProjectileClass;
	void Fire() override;
public:

};
