// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GunBase.h"
#include "Camera/CameraComponent.h"
#include "TPSCharacterBase.generated.h"

UCLASS()
class ASSIGNMENT2_API ATPSCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSCharacterBase();

	UPROPERTY(BlueprintReadWrite, Category=Gun)
	AGunBase* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AProjectileBase> GrenadeClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UCameraComponent* Camera;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetGun(AGunBase* GunActor);

	UFUNCTION(BlueprintCallable)
	FRotator GetAimmingDirection();

	UFUNCTION(BlueprintCallable)
	void Throw(const FVector Location, const FRotator Direction);
};