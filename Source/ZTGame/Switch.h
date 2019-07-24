// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include <Runtime\Engine\Classes\Engine\Light.h>
#include "Switch.generated.h"

UCLASS()
class ZTGAME_API ASwitch : public ATriggerVolume
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwitch();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappingActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappingActor, class AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		ALight* Light;

	//UPROPERTY()
		//int32 CountdownTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Helper function for turning the light on and off
	void SetLightEnabled(bool b);
};
