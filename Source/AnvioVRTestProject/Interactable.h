// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

#define COLLISION_INTERACTABLE ECC_GameTraceChannel1

class AAnvioVRTestProjectCharacter;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()

};

/**
 * 
 */
class ANVIOVRTESTPROJECT_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
	bool CanInteract(AAnvioVRTestProjectCharacter* InInstigator);

	UFUNCTION(BlueprintNativeEvent, Category = Interactable)
	void Interact(AAnvioVRTestProjectCharacter* InInstigator);
};
