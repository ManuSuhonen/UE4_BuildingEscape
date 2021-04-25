// Fill out your copyright notice in the Description page of Project Settings.
#include "WorldPosition.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
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

	auto owner = GetOwner();
	owner->GetRootComponent()->SetMobility(EComponentMobility::Type::Movable);


	FString name = this->GetName();
	FString ownerName = this->GetOwner()->GetName();
	FString location = this->GetOwner()->GetTransform().GetLocation().ToString();


	//UE_LOG(LogTemp,Display, TEXT("%s's owner is %s. Location is %s"),*name,*ownerName,*location);



}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	auto func = [&]() mutable -> void
	{
		auto owner = GetOwner();
		auto X = owner->GetActorLocation().X;
		auto Y = owner->GetActorLocation().Y;

		#define time() UGameplayStatics::GetRealTimeSeconds(GetWorld())

		auto sin = (FMath::Sin(time())+1)*30;

		const FVector NewLocation(X,Y,sin+70);
		owner->SetActorLocation(NewLocation);
	};

	func();
}

