// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameMode.h"

#include <Kismet/GameplayStatics.h>
#include "GroupCamera.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerStart.h"

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
		//UGameplayStatics::CreatePlayer(GetWorld());
	}

}

void ADefaultGameMode::BeginPlay()
{
	for (FConstPlayerControllerIterator iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		APlayerController *playerController = iterator->Get();

		if (playerController && playerController->PlayerState && !MustSpectate(playerController))
		{
			Players.Add(playerController);
		}
	}

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Count: %d"), Players.Num());

}

TArray<AController*>& ADefaultGameMode::GetPlayersRef()
{
	return Players;
}
