// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerSelectionController.generated.h"

/**
 * 
 */
UCLASS()
class MOVERGAME_API APlayerSelectionController : public APlayerController
{
	GENERATED_BODY()

public:
	int ControllerID;

	UPROPERTY(BlueprintReadWrite, Replicated, ReplicatedUsing = OnRep_PlayerID)
	int PlayerID;


public:
	APlayerSelectionController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_PlayerID();

	UFUNCTION(BlueprintCallable)
	void ServerTravel(const FString& inURL, bool bAbsolute = false, bool bShouldSkipGameNotify = false);
	
protected:
	virtual void BeginPlay() override;
};
