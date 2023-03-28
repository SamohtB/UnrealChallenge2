// Copyright Epic Games, Inc. All Rights Reserved.


#include "TP_WeaponComponent.h"
#include "UnrealChallenge02Character.h"
#include "UnrealChallenge02Projectile.h"
//#include "UnrealChallenge02Projectile1.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}


void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Test Projectiles: %i"), ProjectileClass != nullptr && ProjectileClass1 != nullptr && ProjectileClass2 != nullptr && ProjectileClass3 != nullptr);
	// Try and fire a projectile
	if (ProjectileClass != nullptr && ProjectileClass1 != nullptr && ProjectileClass2 != nullptr && ProjectileClass3 != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			BulletType = Character->GetBulletType();
			
			// Spawn the projectile at the muzzle
			//World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			switch(BulletType)
			{
			case 0:
				World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("0"));
				break;
			case 1:
				World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass1, SpawnLocation, SpawnRotation, ActorSpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("1"));
				break;
			case 2:
				World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass2, SpawnLocation, SpawnRotation, ActorSpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("2"));
				break;
			case 3:
				World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass3, SpawnLocation, SpawnRotation, ActorSpawnParams);
				UE_LOG(LogTemp, Warning, TEXT("3"));
				break;
			default:
				World->SpawnActor<AUnrealChallenge02Projectile>(ProjectileClass3, SpawnLocation, SpawnRotation, ActorSpawnParams);
				break;
			}
			
		}
	}
	
	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void UTP_WeaponComponent::AttachWeapon(AUnrealChallenge02Character* TargetCharacter)
{
    UE_LOG(LogTemp, Warning, TEXT("wow0"));
    
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("wow1"));
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	
	// switch bHasRifle so the animation blueprint can switch to another animation set
	Character->SetHasRifle(true);

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}