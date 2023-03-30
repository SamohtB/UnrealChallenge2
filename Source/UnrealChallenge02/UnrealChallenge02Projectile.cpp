// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealChallenge02Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PowerUp.h"
#include "DSP/AudioDebuggingUtilities.h"

AUnrealChallenge02Projectile::AUnrealChallenge02Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AUnrealChallenge02Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 0.f;
}

void AUnrealChallenge02Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->GetCollisionObjectType() == ECC_Destructible)
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		UE_LOG(LogTemp, Warning, TEXT("HIT OBJECT"));
		
		//FActorSpawnParameters ActorSpawnParams;
		//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		/*
		int random = rand() % 4;

		switch(random)
		{
		case 0:
			GetWorld()->SpawnActor<APowerUp>(PowerUpClass, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), ActorSpawnParams);
			break;
		case 1:
			GetWorld()->SpawnActor<APowerUp>(PowerUpClass1, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), ActorSpawnParams);
			break;
		case 2:
			GetWorld()->SpawnActor<APowerUp>(PowerUpClass2, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), ActorSpawnParams);
			break;
		case 3:
			GetWorld()->SpawnActor<APowerUp>(PowerUpClass3, OtherActor->GetActorLocation(), OtherActor->GetActorRotation(), ActorSpawnParams);
			break;
		default:
			break;
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Hello"));

		Destroy();
		*/
	}
}