// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwnningComp, float, NewHealth,float,MaxHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	
	
	// EditAnywhere - Edit in NP Editor and per-instance in level.
	// VisibleAnywhere - 'read only' in editor and level (use for component)
	// EditDefaultsOnly - hide variable per instance, edit in BP editor only.
	// VisibleDefaultsOnly - readonly access for variable, only in BP editor (uncommon)
	// --
	// BlueprintReadOnly - read only in the blueprint scripting (does not affect details panel)
	// BlueprintReadWrite - read write access in blueprints.
	// --
	// Category = "" - display only for detail panels and blueprint context menu.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	//HealthMax, Stamina, Strength, Mana, Critical Hit chance





public:	

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);



		
};
