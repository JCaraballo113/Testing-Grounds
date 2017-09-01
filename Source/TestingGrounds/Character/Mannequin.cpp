// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/ChildActorComponent.h"
#include "Weapons/Gun.h"
#include "Runtime/UMG/Public/Components/Widget.h"


// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the default Subobjects
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->RelativeLocation = FVector(0.f, 0.f, 30.f);
	CameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom);
	PlayerCamera->bAutoActivate = false;

	FPCam = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCam"));
	FPCam->SetupAttachment(GetCapsuleComponent());
	FPCam->RelativeLocation = FVector(-39.56f, 1.75f, 64.f);
	FPCam->bUsePawnControlRotation = true;

	FPArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArms"));
	FPArms->SetOnlyOwnerSee(true);
	FPArms->SetupAttachment(FPCam);
	FPArms->bCastDynamicShadow = false;
	FPArms->CastShadow = false;
	FPArms->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	FPArms->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	Health = StartingHealth;

	if (GunBlueprint == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent(FPArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint")); //Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	Gun->AnimInstance = FPArms->GetAnimInstance();

	if (InputComponent != NULL)
	{
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMannequin::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Damaged"));
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	auto DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, Health);

	Health -= DamageToApply;

	if (IsDead())
	{
		DetachFromControllerPendingDestroy();
	}

	return DamageToApply;
}

void AMannequin::PullTrigger() 
{
	Gun->Fire();
}

bool AMannequin::IsDead() const
{
	return Health <= 0;
}

float AMannequin::GetHealthPercentage() const
{
	return Health / StartingHealth;
}

