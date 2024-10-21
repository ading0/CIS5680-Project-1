// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "DefaultGameMode.h"

static const FName Name_CharacterMotionComponent(TEXT("MoverComponent"));

// Sets default values
APlayerPawn::APlayerPawn()
{
	CharacterMotionComponent = CreateDefaultSubobject<UCharacterMoverComponent>(Name_CharacterMotionComponent);
	ensure(CharacterMotionComponent);

	PrimaryActorTick.bCanEverTick = true;

	SetReplicatingMovement(false);	// disable Actor-level movement replication, since our Mover component will handle it

	auto IsImplementedInBlueprint = [](const UFunction* Func) -> bool
		{
			return Func && ensure(Func->GetOuter())
				&& Func->GetOuter()->IsA(UBlueprintGeneratedClass::StaticClass());
		};

	static FName ProduceInputBPFuncName = FName(TEXT("OnProduceInputInBlueprint"));
	UFunction* ProduceInputFunction = GetClass()->FindFunctionByName(ProduceInputBPFuncName);
	bHasProduceInputinBpFunc = IsImplementedInBlueprint(ProduceInputFunction);

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// Set Camera
	ADefaultGameMode* gamemode = Cast<ADefaultGameMode>(GetWorld()->GetAuthGameMode());
	APlayerController* controller = Cast<APlayerController>(GetController());

	if (gamemode && controller && gamemode->GroupCameraRef)
	{
		controller->SetViewTarget(gamemode->GroupCameraRef->GetAttachParentActor());
	}

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void APlayerPawn::ProduceInput_Implementation(int32 SimTimeMs, FMoverInputCmdContext& InputCmdResult)
{
	if (bHasProduceInputinBpFunc)
	{
		InputCmdResult = OnProduceInputInBlueprint((float)SimTimeMs, InputCmdResult);
	}
}

