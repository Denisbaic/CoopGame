// Fill out your copyright notice in the Description page of Project Settings.


#include "SShotgunWeapon.h"
#include "Math/RandomStream.h"
#include "Engine/World.h"
#include "CoopGame/CoopGame.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

ASShotgunWeapon::ASShotgunWeapon():Super()
{
}

void ASShotgunWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		FHitResult Hit;
		TArray<FVector> TracerEndPoint;
		for (int i = 0; i < BulletsInOneFire; ++i)
		{
			float RandPitch = Rand.FRandRange(YMin, YMax);
			//float RandRoll = Rand.FRandRange(-WeaponScatter.Roll, WeaponScatter.Roll);
			float RandYaw = Rand.FRandRange(XMin, XMax);
			FVector ShotDirection = FRotator(RandPitch, RandYaw, 0.f).Add(EyeRotation.Pitch,EyeRotation.Yaw,EyeRotation.Roll).Vector();
			FVector TraceEnd = EyeLocation + (ShotDirection * 10000);
			if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, COLLISION_WEAPON, QueryParams))
			{
				EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
				float ActualDamage = BaseDamage;
				if (SurfaceType == SURFACE_FLESHVULNERABLE)
				{
					ActualDamage *= 4.f;
				}
				//DrawDebugSphere(GetWorld(), Hit.Location, 5.f, 12, FColor::Red, false, 1.f, 0, 1.f);
				TraceEnd = Hit.Location;
				UGameplayStatics::ApplyPointDamage(Hit.GetActor(), ActualDamage, ShotDirection, Hit, MyOwner->GetInstigatorController(), this, DamageType);
			
				UParticleSystem* SelectedEffect = nullptr;
				switch (SurfaceType)
				{
				case SURFACE_FLESHDEFAULT:
				case SURFACE_FLESHVULNERABLE:
					SelectedEffect = FleshImpactEffect;
					break;
				default:
					SelectedEffect = DefaultImpactEffect;
					break;
				}
				
				if (SelectedEffect)
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
			}
			TracerEndPoint.Add(TraceEnd);
			
			//DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.f, 0, 1.f);
		}
		PlayFireEffects(TracerEndPoint);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void ASShotgunWeapon::PlayFireEffects(TArray<FVector>& TracerEndPoint)
{
	if (MuzzleEffect)
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComponent, MuzzleSocketName);
	if (TracerEffect)
	{
		FVector MuzzleLocation = MeshComponent->GetSocketLocation(MuzzleSocketName);
		for (int i = 0; i < TracerEndPoint.Num(); ++i)
		{
			UParticleSystemComponent* TempEmitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, MuzzleLocation);
			if (TempEmitter)
			{
				TempEmitter->SetVectorParameter(TracerTargetName, TracerEndPoint[i]);
			}
		}
	}
	APawn* MyOwner = Cast<APawn>(GetOwner());
	if (MyOwner)
	{
		APlayerController* PC = Cast<APlayerController>(MyOwner->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}
	if (SoundOfFire)
		UGameplayStatics::PlaySound2D(GetWorld(), SoundOfFire);
}
