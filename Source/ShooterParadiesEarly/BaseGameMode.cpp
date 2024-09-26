// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameMode.h"
#include "BaseCharakter.h"

void ABaseGameMode::BeginPlay()
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
