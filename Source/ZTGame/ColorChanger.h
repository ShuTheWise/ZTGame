// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Runtime\Engine\Classes\Engine\Light.h>
#include "ColorChanger.generated.h"

UCLASS()
class ZTGAME_API AColorChanger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AColorChanger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadOnly, interp, Category = ColorChanger, meta = (HideAlphaChannel))
		FColor LightColor;

	UPROPERTY(EditAnywhere)
		ALight* Light;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
