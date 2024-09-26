// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterParadiesEarlyGameModeBase.h"
#include "BaseCharakter.h"

void AShooterParadiesEarlyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharakter* myCharacter = Cast<ABaseCharakter>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (HUDClass != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
}
