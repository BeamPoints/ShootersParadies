// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"
#include "collision/PxCollisionDefs.h"

// Sets default values for this component's properties
UBaseWeapon::UBaseWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<USphereComponent>(TEXT("WPN_Trigger"));
	collision->InitSphereRadius(48.0f);
	


}


// Called when the game starts
void UBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

