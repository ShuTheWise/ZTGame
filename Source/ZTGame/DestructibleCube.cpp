// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleCube.h"
#include "UnrealNetwork.h"

// Sets default values
ADestructibleCube::ADestructibleCube()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DestructibleComponent"));
	DestructibleComponent->SetNotifyRigidBodyCollision(true);
}

// Called when the game starts or when spawned
void ADestructibleCube::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	DestructibleComponent->OnComponentHit.AddDynamic(this, &ADestructibleCube::OnCompHit);
}

void ADestructibleCube::Destruct(float DamageAmount, FVector HitLoc, FVector HitDir, float ImpulseStrength)
{
	if (!DestructibleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing DestructibleComponent !!!"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("cube destroyed"));
	DestructibleComponent->ApplyRadiusDamage(DamageAmount, HitLoc, DefaultDamageRadius, ImpulseStrength, true);
}

void ADestructibleCube::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor->ActorHasTag("Projectile") || bDestroyed) return;

	if (Role == ROLE_Authority)
	{
		RegisterHit(Hit, NormalImpulse);
	}
	else
	{
		ServerRegisterHit(Hit, NormalImpulse);
	}
}

void ADestructibleCube::RegisterHit(const FHitResult& Hit, const FVector& NormalImpulse)
{
	UE_LOG(LogTemp, Error, TEXT("cube hit"));

	CurrentHealth -= 1.f;
	if (CurrentHealth <= 0.0f)
	{
		bDestroyed = true;
		Destruct(DefaultDamageAmount, Hit.Location, NormalImpulse, DefaultImpulseStrength);
	}
}

bool ADestructibleCube::ServerRegisterHit_Validate(const FHitResult& Hit, const FVector& NormalImpulse)
{
	return true;
}

void ADestructibleCube::ServerRegisterHit_Implementation(const FHitResult& Hit, const FVector& NormalImpulse)
{
	if (Role == ROLE_Authority)
	{
		RegisterHit(Hit, NormalImpulse);
	}
}

void ADestructibleCube::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ADestructibleCube, CurrentHealth);
}
