// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{


	// ...

	Health = 100;
	MaxHealth = 100;
}




bool USAttributeComponent::ApplyHealthChange(float Delta)
{

	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, MaxHealth, Delta);

	return true;

}



