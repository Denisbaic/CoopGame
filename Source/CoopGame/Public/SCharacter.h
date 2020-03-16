// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);

	void BeginCrouch();
	void EndCrouch();
	void BeginJump();
	void EndJump();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
		class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USHealthComponent* HealthComponent;

	bool bWantsToZoom;
	UPROPERTY(EditDefaultsOnly, Category = "Player")
		float ZoomedFOV;
	/*Default FOV set during begin play*/	
	float DefaultFOV;
	UPROPERTY(EditDefaultsOnly, Category = "Player",meta=(ClampMin=0.1,ClampMax=100))
		float ZoomInterpSpeed;

	void BeginZoom();
	void EndZoom();

	UPROPERTY(Replicated,BlueprintReadWrite)
		class ASWeapon* CurrentWeapon;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASWeapon> StarterWeaponClass;
	void StartFire();
	void StopFire();
	UPROPERTY(VisibleDefaultsOnly,Category="Player")
		FName WeaponSocketName;

	UFUNCTION()
		void OnHealthChanged(USHealthComponent* OwningHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UPROPERTY(BlueprintReadOnly,Category="Player")
		bool bDied;
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;


};
