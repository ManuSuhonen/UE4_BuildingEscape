// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldPosition.h"
#include "Kismet/GameplayStatics.h"

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


	auto world = this->GetOwner()->GetWorld();

	TArray<AActor*> AllActors;
  	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AActor::StaticClass(),AllActors);
	
	for (auto &&i : AllActors)
	{
		UE_LOG(LogTemp,Error, TEXT("Hellos from %s"),*(i->GetName()));
	}

	UE_LOG(LogTemp,Error, TEXT("Hellos from %i"),AllActors.Num());

	//auto name = StaticClass()->GetName();
	UE_LOG(LogTemp,Error, TEXT("Hellos from %s"),*(world->GetName()));
	//UE_LOG(LogTemp,Error, TEXT("children count %i"),name->GetComponents().Num());
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

