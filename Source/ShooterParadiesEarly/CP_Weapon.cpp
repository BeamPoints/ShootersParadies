// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h" 
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UCP_Weapon::UCP_Weapon()
{
	// Default offset from the character location for projectiles to spawn
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UCP_Weapon::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr) {return;}
	

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (mag_Ammonation != 0)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// Spawn the projectile at the muzzle
				World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

				mag_Ammonation--;


				// Try and play the sound if specified
				if (FireSound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
				}

				/*// Try and play a firing animation if specified
				if (FireAnimation != nullptr)
				{
					// Get the animation object for the arms mesh
					UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance();
					if (AnimInstance != nullptr)
					{
						AnimInstance->Montage_Play(FireAnimation, 1.f);
					}
				}
				*/
			}
		}
	}
}

void UCP_Weapon::Reload()
{
	if (mag_Ammonation != 30 && ammonation != 0)
	{
		while (mag_Ammonation != 30 && ammonation != 0)
		{
			mag_Ammonation++;
			ammonation--;
		}
	}
}

void UCP_Weapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character != nullptr)
	{
		// Unregister from the OnUseItem Event
		Character->OnUseItem.RemoveDynamic(this, &UCP_Weapon::Fire);
	}
}
