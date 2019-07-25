// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "DestructibleCube.generated.h"

UCLASS()
class ZTGAME_API ADestructibleCube : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADestructibleCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxHealth = 3.f;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float DefaultDamageAmount = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float DefaultImpulseStrength = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Stats")
		float DefaultDamageRadius = 1.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		float CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
		bool bDestroyed;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
		UDestructibleComponent* DestructibleComponent;

	void Destruct(float DamageAmount, FVector HitLoc, FVector HitDir, float ImpulseStrength);

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
