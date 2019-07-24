// Fill out your copyright notice in the Description page of Project Settings.
#include "ColorChanger.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Components/BoxComponent.h"

// Sets default values
AColorChanger::AColorChanger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetSimulatePhysics(false);
	BoxComponent->SetNotifyRigidBodyCollision(true);
	BoxComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	BoxComponent->OnComponentHit.AddDynamic(this, &AColorChanger::OnCompHit);

	// Set as root component
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void AColorChanger::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* staticMesh = this->FindComponentByClass<UStaticMeshComponent>();
	if (staticMesh != nullptr)
	{
		UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(staticMesh->GetMaterial(0), NULL);

		if (material != nullptr)
		{
			material->SetVectorParameterValue(FName(TEXT("DiffuseColor")), LightColor);
			staticMesh->SetMaterial(0, material);
			return;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("chaning color on %s failed"),*GetName());
}

// Called every frame
void AColorChanger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AColorChanger::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s, setting new color"), *OtherActor->GetName()));
		if (Light)
			Light->SetLightColor(LightColor);
	}
}