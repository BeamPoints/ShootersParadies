// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config = Game)
class SHOOTERPARADIESEARLY_API AProjectile : public AActor
{
	GENERATED_BODY()

	/// UPROPERTYS

	UPROPERTY(EditAnywhere, Category = Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	/// </UPROPERTYS>

public:	

	AProjectile();

	/// PUBLIC UPROPERTYS PROJECTILE SETTINGS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile_Settings)
	float collisionRadius = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile_Settings)
	float initialSpeed = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile_Settings)
	float maxSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile_Settings)
	bool rotationFollowsVelocity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile_Settings)
	bool canBounce = true;

	/// PUBLIC </UPROPERTYS> PROJECTILE SETTINGS

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }


};
