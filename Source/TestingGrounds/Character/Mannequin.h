// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetGunAttatchment();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void PullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Health")
		bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealthPercentage() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<class AGun> GunBlueprint;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCam;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	class USkeletalMeshComponent* FPArms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class AGun* Gun;

	UPROPERTY(EditAnywhere, Category = "Health")
		float StartingHealth = 100;


	float Health;
};
