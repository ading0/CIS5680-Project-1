// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameMode.h"

#include <Kismet/GameplayStatics.h>
#include "GroupCamera.h"
#include "PlayerCharacter.h"

void ADefaultGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	TArray<AActor*> cameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGroupCamera::StaticClass(), cameras);
	if (cameras.Num())
	{
		AGroupCamera *mainCamera = (AGroupCamera*)cameras[0];
		GroupCameraRef = mainCamera->GetCameraComponent();
	}

	const int NUM_PLAYERS = 2;
	for (int playerCount = 1; playerCount < NUM_PLAYERS; ++playerCount)
	{
		UGameplayStatics::CreatePlayer(GetWorld());
	}

}

void ADefaultGameMode::BeginPlay()
{
	for (FConstPlayerControllerIterator iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		APlayerController *actor = iterator->Get();
		if (actor && actor->PlayerState && !MustSpectate(actor))
		{
			Players.Add(actor->GetPawn());
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Player Count: %d"), Players.Num());

}
