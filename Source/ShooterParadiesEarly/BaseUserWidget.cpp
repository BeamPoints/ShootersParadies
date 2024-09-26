// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"

void UBaseUserWidget::SetHealth(float currentHealh, float maxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(currentHealh / maxHealth);
	}
}

void UBaseUserWidget::SetStamina(float currentStamina, float maxStamina)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(currentStamina / maxStamina)
	}
}
