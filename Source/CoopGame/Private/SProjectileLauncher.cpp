// Fill out your copyright notice in the Description page of Project Settings.

#include "CoopGame/Public/SProjectileLauncher.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CoopGame/Public/SCharacter.h"

ASProjectileLauncher::ASProjectileLauncher():Super()
{
}

void ASProjectileLauncher::Fire()
{
	ASCharacter* MyOwner = Cast<ASCharacter>(GetOwner());
	if(MyOwner && ProjectileClass)
	{
		FVector ViewPoint;
		FRotator ViewRotation;
		MyOwner->GetActorEyesViewPoint(ViewPoint, ViewRotation);
		FVector TraceEnd=ViewPoint+ViewRotation.Vector()*10000;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult HitResult;
		if(GetWorld()->LineTraceSingleByChannel(HitResult,ViewPoint,TraceEnd,ECC_Visibility, QueryParams))
		{
			TraceEnd = HitResult.Location;
		}
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.Instigator = MyOwner;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		FVector MuzzleLocation = GetMuzzleTransform().GetLocation();
		FRotator ShotDirection = (TraceEnd - MuzzleLocation).Rotation();
		//DrawDebugLine(GetWorld(), MuzzleLocation, TraceEnd, FColor::Red, false, 3.f, 0, 3.f);

		GetWorld()->SpawnActor(ProjectileClass, &MuzzleLocation, &ShotDirection, ActorSpawnParameters);
	}
}
