// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Terminal.generated.h"

class USkeletalMeshComponent;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class ANVIOVRTESTPROJECT_API ATerminal
	: public AActor
	, public IInteractable
{
	GENERATED_BODY()
	
public:	

	ATerminal();

protected:

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
	TScriptInterface<IInteractable> Key;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Access)
	bool bTerminalActivated = false;

	UFUNCTION(BlueprintImplementableEvent, Category = Activation)
	void OnInteracted(bool IsSuccess);
};
