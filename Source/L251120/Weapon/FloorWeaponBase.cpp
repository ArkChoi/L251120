// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AFloorWeaponBase::AFloorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AFloorWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

