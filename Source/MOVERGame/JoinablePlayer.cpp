// Fill out your copyright notice in the Description page of Project Settings.


#include "JoinablePlayer.h"

void UJoinablePlayer::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	TArray<UWidgetSwitcher*> WidgetSwitchers;
	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		if (UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(Widget))
		{
			WidgetSwitchers.Add(Switcher);
		}
	});
	if (WidgetSwitchers.Num() > 0) StatusSwitcher = WidgetSwitchers[0];
}

void UJoinablePlayer::GetStatus(TEnumAsByte<JoinStatus>& _Status)
{
	_Status = Status;
}

void UJoinablePlayer::MakeAvailable()
{
	Status = JoinStatus::AVAILABLE;
	StatusSwitcher->SetActiveWidgetIndex(Status);
}

void UJoinablePlayer::MakeOccupied()
{
	Status = JoinStatus::OCCUPIED;
	StatusSwitcher->SetActiveWidgetIndex(Status);
}
