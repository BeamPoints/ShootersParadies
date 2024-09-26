// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/Object.h"

/**
 * 
class SHOOTERPARADIESEARLY_API ActorHelper
{
public:
	ActorHelper();
	~ActorHelper();
};
 */

namespace ActorHelper
{
	template <class ObjectType>
	auto FindObject(const FString& a_obj) -> ObjectType*
	{
		return ConstructorHelpers::FObjectFinder<ObjectType>(*a_obj).Object;
	}
}
