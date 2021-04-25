// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//this->GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);

	auto rotate = this->GetOwner()->GetActorRotation();

	UE_LOG(LogTemp,Display, TEXT("%s"),*rotate.ToString());

	rotate.Yaw = 270;

	GetOwner()->SetActorRotation(rotate);

}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

