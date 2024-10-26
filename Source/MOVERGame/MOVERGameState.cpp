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

void AMOVERGameState::IsControllerJoined(int ControllerID, bool& Result, int& Index)
{
	for (int i = 0; i < SelectionStates.Num(); ++i)
	{
		FSelectionState state = SelectionStates[i];
		if (state.ControllerID == ControllerID)
		{
			Result = true;
			Index = i;
			return;
		}
	}
	Index = -1;
	Result = false;
}
