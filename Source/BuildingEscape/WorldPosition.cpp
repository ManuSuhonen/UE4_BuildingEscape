// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldPosition.h"
#include "GameFramework/Actor.h"

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

	UE_LOG(LogTemp,Error, TEXT("this component is attached to: %s"),*(owner->GetName()));


	AActor* actor = owner->GetOwner();
	
	if(actor == nullptr)
	{
		UE_LOG(LogTemp,Error, TEXT("owner is: null"));
	}
	else
	{
		UE_LOG(LogTemp,Error, TEXT("owner is not null"));
	}
	
	//UE_LOG(LogTemp,Error, TEXT("owners parent is: %i"),actor == nullptr);
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

