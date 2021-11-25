// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATPSCharacterBase::ATPSCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
}
// Called when the game starts or when spawned
void ATPSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}




void ATPSCharacterBase::SetGun(AGunBase* GunActor)
{
	Gun = GunActor;
	USkeletalMeshComponent* GunMesh = Gun->GunMesh;
	GunMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	GunMesh->SetSimulatePhysics(false);
	GunMesh->AttachToComponent(GetMesh(),
							   FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
							   TEXT("index_03_r"));
	GunMesh->SetRelativeTransform(Gun->GunTrans);
	Gun->GunOwner = this;
}

FRotator ATPSCharacterBase::GetAimmingDirection()
{
	FVector TraceStartPos = Camera->GetComponentLocation();
	FVector TraceEndPos = TraceStartPos + Camera->GetForwardVector() * 10000.f;

	FVector TargetPos = TraceEndPos;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	FHitResult HitRes;

	if(GetWorld()->LineTraceSingleByChannel(HitRes, TraceStartPos, TraceEndPos, ECC_Visibility, QueryParams))
	{
		TargetPos = HitRes.ImpactPoint;
	}

	return UKismetMathLibrary::FindLookAtRotation(Gun->MuzzleLocation->GetComponentLocation(), TargetPos);
}

void ATPSCharacterBase::Throw(const FVector Location, const FRotator Direction)
{
	if (GrenadeClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			AProjectileBase* Grenade =  World->SpawnActor<AProjectileBase>(GrenadeClass, Location, Direction, ActorSpawnParams);
			Grenade->ProjMesh->AddImpulse(Direction.Vector() * 3000.f);
		}
	}
}


