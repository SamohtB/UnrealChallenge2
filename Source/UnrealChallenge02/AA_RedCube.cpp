// Fill out your copyright notice in the Description page of Project Settings.


#include "AA_RedCube.h"

// Sets default values
AAA_RedCube::AAA_RedCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsIndestructible = true;

}

// Called when the game starts or when spawned
void AAA_RedCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAA_RedCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

