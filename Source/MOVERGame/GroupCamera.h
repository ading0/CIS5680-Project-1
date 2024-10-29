// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include "GroupCamera.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MOVERGAME_API AGroupCamera : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Default")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Default")
	TObjectPtr<UCameraComponent> Camera;

	static FName MeshComponentName;
	static FName SpringArmComponentName;
	static FName CameraComponentName;

	UStaticMeshComponent* GetMeshComponent() const { return Mesh; }
	USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }
	UCameraComponent* GetCameraComponent() const { return Camera; }
	
public:	
	// Sets default values for this actor's properties
	AGroupCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
