// Fill out your copyright notice in the Description page of Project Settings.


#include <Net/UnrealNetwork.h>

#include "MOVERGameState.h"

AMOVERGameState::AMOVERGameState(const FObjectInitializer& ObjectInitializer)
	: UIStateUpdated(),
	  SelectionStates()
{
	
}

void AMOVERGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMOVERGameState, SelectionStates);
}

void AMOVERGameState::OnRep_SelectionStates()
{
	UIStateUpdated.Broadcast();
}

void AMOVERGameState::IsControllerJoined(int ControllerID, bool& Result, int& PlayerIndex)
{
	for (int i = 0; i < SelectionStates.Num(); ++i)
	{
		FSelectionState& state = SelectionStates[i];
		if (state.ControllerID == ControllerID)
		{
			Result = true;
			PlayerIndex = i;
			return;
		}
	}

	Result = false;
	PlayerIndex = -1;
}

void AMOVERGameState::FindAvailableSlot(bool& Success, FSelectionState& SelectionState, int& PlayerIndex)
{
	for (int i = 0; i < SelectionStates.Num(); ++i)
	{
		FSelectionState& state = SelectionStates[i];
		if (state.ControllerID < 0)
		{
			Success = true;
			SelectionState = state;
			PlayerIndex = i;
			return;
		}
	}

	Success = false;
	PlayerIndex = -1;
}

void AMOVERGameState::ResetSelectionStateList(int NumStates)
{
	SelectionStates.Init({}, NumStates);
}

void AMOVERGameState::ResetSelectionState(int PlayerIndex)
{
	if (PlayerIndex < 0 || PlayerIndex >= SelectionStates.Num()) return;

	SelectionStates[PlayerIndex] = FSelectionState();
}

void AMOVERGameState::SetSelectionState(FSelectionState SelectionState, int PlayerIndex)
{
	if (PlayerIndex < 0 || PlayerIndex >= SelectionStates.Num()) return;

	SelectionStates[PlayerIndex] = SelectionState;
}

void AMOVERGameState::GetSelectionState(int PlayerIndex, FSelectionState& SelectionState)
{
	if (PlayerIndex < 0 || PlayerIndex >= SelectionStates.Num()) return;

	SelectionState = SelectionStates[PlayerIndex];
}
