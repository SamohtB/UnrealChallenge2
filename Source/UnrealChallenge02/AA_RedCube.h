// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AA_RedCube.generated.h"

UCLASS()
class UNREALCHALLENGE02_API AAA_RedCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAA_RedCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	bool bIsIndestructible;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
