// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleCube.h"

// Sets default values
ADestructibleCube::ADestructibleCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ADestructibleCube::Hit(int32 HitAmount)
{
	Health -= HitAmount;
	if (Health < 1) 
	{
		Destruct();
	}
}

// Called when the game starts or when spawned
void ADestructibleCube::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructibleCube::Destruct()
{
	Destroy();
}

