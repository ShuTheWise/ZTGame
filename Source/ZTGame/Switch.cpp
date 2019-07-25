// Fill out your copyright notice in the Description page of Project Settings.
#include "Switch.h"
#include "Net/UnrealNetwork.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASwitch::ASwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &ASwitch::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ASwitch::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ASwitch::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Emerald, true, -1, 0, 5);
}

void ASwitch::OnOverlapBegin(AActor* OverlappingActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		//activate the light
		SetLightEnabled(true);
	}
}

void ASwitch::OnOverlapEnd(AActor* OverlappingActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this)) {
		//deactive the light
		SetLightEnabled(false);
	}
}

void ASwitch::SetLightEnabled(bool b)
{
	if (Light) {
		FString s = b ? "on" : "off";
		Light->SetEnabled(b);
	}
}