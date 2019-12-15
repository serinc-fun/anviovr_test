// Fill out your copyright notice in the Description page of Project Settings.


#include "Terminal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "AnvioVRTestProjectCharacter.h"
#include "Materials/MaterialInstanceDynamic.h"

void FMaterialAnimationColorData::UpdateCurrentColor(UMaterialInstanceDynamic* InMID)
{
	if (InMID && InMID->IsValidLowLevel())
	{
		FMaterialParameterInfo ParameterInfo(ParameterName);
		InMID->GetVectorParameterValue(ParameterInfo, CurrentColor);
	}
}

void FMaterialAnimationColorData::BlendColorData(UMaterialInstanceDynamic* InMID, float InBlendValue)
{
	if (InMID && InMID->IsValidLowLevel())
	{
		InMID->SetVectorParameterValue(ParameterName, FMath::Lerp(CurrentColor, TargetColor, InBlendValue));
	}
}

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

void ATerminal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ButtonMID == nullptr)
	{
		ButtonMID = ButtonMesh->CreateAndSetMaterialInstanceDynamic(0);
	}

	AnimationPulseColor.ParameterName = ParamNameColor;
	AnimationGridColor.ParameterName = ParamNameSubColor;
	
	AnimationTimeline.AddInterpFloat(CurvePush, FOnTimelineFloatStatic::CreateUObject(this, &ATerminal::OnUpdatePushCurve));
	AnimationTimeline.AddInterpFloat(CurveColor, FOnTimelineFloatStatic::CreateUObject(this, &ATerminal::OnUpdateColorCurve));

	OnInteracted(bTerminalActivated, true);
}

void ATerminal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (AnimationTimeline.IsPlaying())
	{
		AnimationTimeline.TickTimeline(DeltaSeconds);
	}
}

bool ATerminal::CanInteract_Implementation(AAnvioVRTestProjectCharacter* InInstigator)
{
	return true;
}

void ATerminal::Interact_Implementation(AAnvioVRTestProjectCharacter* InInstigator)
{
	if (InInstigator && InInstigator->IsValidLowLevel())
	{
		auto InstigatorInventory = InInstigator->GetInventoryItems();
		for (auto& TargetItem : InstigatorInventory)
		{
			if (TargetItem.GetObject() && (Key && TargetItem.GetObject() == Key || Key == nullptr && TargetItem.GetObject()->GetClass() == KeyType))
			{
				if (InInstigator->RemoveFromInventory(TargetItem))
				{
					bTerminalActivated = true;
					break;
				}				
			}
		}
	}
	
	OnInteracted(bTerminalActivated);
}

void ATerminal::OnInteracted_Implementation(bool IsSuccess, bool Force /* false */)
{
	AnimationPulseColor.TargetColor = IsSuccess ? ColorPulseActivated : ColorPulseDeactivated;
	AnimationPulseColor.UpdateCurrentColor(ButtonMID);

	AnimationGridColor.TargetColor = IsSuccess ? ColorGridActivated : ColorGridDeactivated;
	AnimationGridColor.UpdateCurrentColor(ButtonMID);

	if (Force)
	{
		OnUpdateColorCurve(1.0f);
	}
	else
	{
		AnimationTimeline.PlayFromStart();
		ButtonMesh->PlayAnimation(PushAnimation, false);
	}
}

void ATerminal::OnUpdatePushCurve(float Value)
{
	if (ButtonMID && ButtonMID->IsValidLowLevel())
	{
		ButtonMID->SetScalarParameterValue(ParamNamePush, Value);
	}
}

void ATerminal::OnUpdateColorCurve(float Value)
{
	AnimationPulseColor.BlendColorData(ButtonMID, Value);
	AnimationGridColor.BlendColorData(ButtonMID, Value);
}
