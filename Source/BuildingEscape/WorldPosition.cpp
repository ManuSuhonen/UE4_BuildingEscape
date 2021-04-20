// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	auto owner = GetOwner();
	owner->GetRootComponent()->SetMobility(EComponentMobility::Type::Movable);
	
	auto trans = owner->GetTransform().GetLocation().ToString();

	UE_LOG(LogTemp,Error, TEXT("this component is attached to: %s"),*(owner->GetName()));
	UE_LOG(LogTemp,Error, TEXT("owners Location is %s"),*trans);
	const FVector NewLocation(1,1,1);
	owner->SetActorLocation(NewLocation);
	UE_LOG(LogTemp,Error, TEXT("owners new Location is %s"),*trans);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

