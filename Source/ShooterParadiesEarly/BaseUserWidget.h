// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"


UCLASS()
class SHOOTERPARADIESEARLY_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetHealth(float currentHealth, float maxHealth);

	void SetStamina(float currentStamina, float maxStamina);

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget));
	class UProgressBar* StaminaBar;
	
};
