// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelection.h"
#include <Net/UnrealNetwork.h>

UPlayerSelection::UPlayerSelection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	  PlayerIndexMap(),
	  JoinablePlayers()
{
	
}

void UPlayerSelection::NativePreConstruct()
{
	Super::NativePreConstruct();

	JoinablePlayers.Empty();
	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		if (UJoinablePlayer* JoinablePlayer = Cast<UJoinablePlayer>(Widget))
		{
			JoinablePlayers.Add(JoinablePlayer);
		}
	});

	MaxPlayerCount = JoinablePlayers.Num();
}

void UPlayerSelection::SetPlayerIndex(int ControllerIndex, int PlayerIndex)
{
	PlayerIndexMap.Add(ControllerIndex, PlayerIndex);
}

void UPlayerSelection::GetPlayerIndex(int ControllerIndex, int& PlayerIndex, bool& Success)
{
	Success = false;

	if (PlayerIndexMap.Contains(ControllerIndex))
	{
		PlayerIndex = PlayerIndexMap[ControllerIndex];
		Success = true;
	}
}
