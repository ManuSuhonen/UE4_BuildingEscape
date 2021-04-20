// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldPosition.h"

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
	// ...
	//auto temp2 = typeid(*this).name();
	//auto temp = __FILE__;
	auto name = this->GetName();
	//auto name = StaticClass()->GetName();
	UE_LOG(LogTemp,Error, TEXT("Hellos from %s"),*name);
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

