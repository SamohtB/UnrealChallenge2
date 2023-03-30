// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealChallenge02Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AUnrealChallenge02Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

public:
	AUnrealChallenge02Projectile();

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp sub object **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement sub object **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UPROPERTY(EditDefaultsOnly, Category=PowerUp)
	TSubclassOf<class APowerUp> PowerUpClass;

	UPROPERTY(EditDefaultsOnly, Category=PowerUp)
	TSubclassOf<class APowerUp> PowerUpClass1;

	UPROPERTY(EditDefaultsOnly, Category=PowerUp)
	TSubclassOf<class APowerUp> PowerUpClass2;

	UPROPERTY(EditDefaultsOnly, Category=PowerUp)
	TSubclassOf<class APowerUp> PowerUpClass3;
};

