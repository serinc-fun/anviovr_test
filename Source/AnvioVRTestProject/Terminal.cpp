// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "AnvioVRTestProjectCharacter.h"

ATerminal::ATerminal()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("USceneComponent"));
	SetRootComponent(Root);

	TerminalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));

	ButtonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Button"));

	ButtonCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ButtonCollision"));
	ButtonCollision->SetupAttachment(ButtonCollision);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
}

bool ATerminal::CanInteract_Implementation(AAnvioVRTestProjectCharacter* InInstigator)
{
	if (InInstigator && InInstigator->IsValidLowLevel())
	{
		return !InInstigator->IsInventoryEmpty();
	}

	return false;
}

void ATerminal::Interact_Implementation(AAnvioVRTestProjectCharacter* InInstigator)
{
	if (InInstigator && InInstigator->IsValidLowLevel())
	{
		auto InstigatorInventory = InInstigator->GetInventoryItems();
		for (auto& TargetItem : InstigatorInventory)
		{
			if (TargetItem.GetObject() && (Key.GetObject() && TargetItem == Key || TargetItem.GetObject()->GetClass() == KeyType))
			{
				if (InInstigator->RemoveFromInventory(TargetItem))
				{
					bTerminalActivated = true;
					OnInteracted(true);

					return;
				}				
			}
		}
	}

	OnInteracted(false);
}
