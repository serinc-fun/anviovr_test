// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Components/TimelineComponent.h"
#include "Terminal.generated.h"

class UAnimationAsset;
class USkeletalMeshComponent;
class UBoxComponent;
class UArrowComponent;

USTRUCT()
struct FMaterialAnimationColorData
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
	FName ParameterName;

	UPROPERTY(EditAnywhere)
	FLinearColor TargetColor;

	void UpdateCurrentColor(UMaterialInstanceDynamic* InMID);
	void BlendColorData(UMaterialInstanceDynamic* InMID, float InBlendValue);
	
private:
	
	UPROPERTY(EditAnywhere)
	FLinearColor CurrentColor;
};

UCLASS()
class ANVIOVRTESTPROJECT_API ATerminal
	: public AActor
	, public IInteractable
{
	GENERATED_BODY()
	
public:	

	ATerminal();

protected:

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual bool CanInteract_Implementation(AAnvioVRTestProjectCharacter* InInstigator) override;
	virtual void Interact_Implementation(AAnvioVRTestProjectCharacter* InInstigator) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* ButtonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* TerminalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* ButtonCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Access)
	TSubclassOf<AActor> KeyType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Access)
	AActor* Key;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Access)
	bool bTerminalActivated = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UCurveFloat* CurvePush;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FName ParamNamePush;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UCurveFloat* CurveColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FName ParamNameColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FName ParamNameSubColor;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLinearColor ColorPulseActivated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLinearColor ColorPulseDeactivated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLinearColor ColorGridActivated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FLinearColor ColorGridDeactivated;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	UAnimationAsset* PushAnimation;
	
	UFUNCTION(BlueprintNativeEvent, Category = Animation)
	void OnInteracted(bool IsSuccess, bool Force = false);

	UFUNCTION()
	void OnUpdatePushCurve(float Value);

	UFUNCTION()
	void OnUpdateColorCurve(float Value);
	
	UPROPERTY(Transient)
	FTimeline AnimationTimeline;

	UPROPERTY(Transient)
	FMaterialAnimationColorData AnimationPulseColor;

	UPROPERTY(Transient)
	FMaterialAnimationColorData AnimationGridColor;
	
	UPROPERTY(Transient)
	UMaterialInstanceDynamic* ButtonMID;
};
