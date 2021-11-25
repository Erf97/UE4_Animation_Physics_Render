// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"
#include "GunBase.generated.h"

UCLASS()
class ASSIGNMENT2_API AGunBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category=Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category=Mesh)
	FTransform GunTrans;
	// 0, 8, -3
	// 0, 0, 200
	// 1, 1, 1
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Mesh)
	USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UArrowComponent* GunArrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAudioComponent* FireAudio;
	
	UPROPERTY(EditAnywhere, Category=Mesh)
	FVector RelativeLocationVector;

	UPROPERTY(VisibleAnywhere)
	ACharacter* GunOwner;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Fire(FRotator Direction);
};
