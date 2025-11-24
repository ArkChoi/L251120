// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class L251120_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TSubclassOf<class AProjectileBase> ProjectileTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FName SocketName = TEXT("HandGrip_R");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxBulletCount = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 CurrentBulletCount = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UAnimMontage> FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<class UAnimMontage> ReloadMontage;
};
