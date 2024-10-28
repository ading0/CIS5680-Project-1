// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Components/MeshComponent.h" // For custom depth properties on mesh components
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Moveable.generated.h"

UCLASS()
class MOVERGAME_API AMoveable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EnableCustomDepth(UStaticMeshComponent* MeshComponent, bool bEnable, int32 StencilValue = 1)
	{
		if (MeshComponent)
		{
			MeshComponent->SetRenderCustomDepth(bEnable);
			MeshComponent->CustomDepthStencilValue = StencilValue;
		}
	}
};
