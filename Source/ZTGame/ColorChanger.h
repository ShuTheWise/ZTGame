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

	UPROPERTY(interp, meta = (HideAlphaChannel))
		FColor LightColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, reliable)
	void SetLightColor();
	void SetLightColor_Implementation();

private:
	UPROPERTY(VisibleAnywhere)
		class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
		ALight* Light;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
