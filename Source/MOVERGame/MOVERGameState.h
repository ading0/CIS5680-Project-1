// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MOVERGameState.generated.h"

USTRUCT(BlueprintType)
struct MOVERGAME_API FSelectionState
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int ControllerID;

	FSelectionState()
		: ControllerID(-1)
	{

	}
};

/**
 * 
 */
UCLASS()
class MOVERGAME_API AMOVERGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIStateUpdated);

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FUIStateUpdated UIStateUpdated;

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_SelectionStates)
	TArray<FSelectionState> SelectionStates;

public:
	AMOVERGameState(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_SelectionStates();

	UFUNCTION(BlueprintCallable)
	void IsControllerJoined(int ControllerID, bool& Result, int& Index);

	UFUNCTION(BlueprintCallable)
	void FindAvailableSlot(bool& Success, FSelectionState& SelectionState, int& PlayerIndex);

	UFUNCTION(BlueprintCallable)
	void SetSelectionState(FSelectionState SelectionState, int PlayerIndex);
};
