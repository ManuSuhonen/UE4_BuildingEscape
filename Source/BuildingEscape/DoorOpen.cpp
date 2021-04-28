// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"

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
	
	//auto rotate = this->GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp,Display, TEXT("%s"),*rotate.ToString());
	//rotate.Yaw = 270;

	//start = {0,180,0};
	//end = {0,270,0};

	//GetOwner()->SetActorRotation({0,270,0});

	initialYaw = GetOwner()->GetActorRotation().Yaw;
	currentYaw = initialYaw;
	targetYaw += initialYaw;

	player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UE_LOG(LogTemp,Display, TEXT("%s"),*player->GetName());

	if(EventDriven == true)
	{
		if(TriggerVolume != nullptr)
		{		
			TriggerVolume->OnActorBeginOverlap.AddDynamic(this,&UDoorOpen::BeginOverlap);
			TriggerVolume->OnActorEndOverlap.AddDynamic(this,&UDoorOpen::EndOverlap);
		}
	}
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp,Display, TEXT("%s"),*start.ToString());

	if(EventDriven == false)
	{
		if(TriggerVolume->IsOverlappingActor(player))
		{
			currentYaw = FMath::FInterpTo(currentYaw,targetYaw,DeltaTime,speed);
			auto rotate = GetOwner()->GetActorRotation();
			rotate.Yaw = currentYaw;
			GetOwner()->SetActorRotation(rotate);
		}
		else
		{
			currentYaw = FMath::FInterpTo(currentYaw,initialYaw,DeltaTime,speed);
			auto rotate = GetOwner()->GetActorRotation();
			rotate.Yaw = currentYaw;
			GetOwner()->SetActorRotation(rotate);
		}
	}
}


void UDoorOpen::BeginOverlap(AActor* Actor, AActor* OtherActor)
{
	UE_LOG(LogTemp,Display, TEXT("overlap detected between %s and %s"),*Actor->GetName(),*OtherActor->GetName());

	//currentYaw = FMath::FInterpTo(currentYaw,targetYaw,DeltaTime,speed);
	auto doorRotation = GetOwner()->GetActorRotation();
	doorRotation.Yaw = currentYaw+90;
	GetOwner()->SetActorRotation(doorRotation);
}

void UDoorOpen::EndOverlap(AActor* Actor, AActor* OtherActor)
{
	UE_LOG(LogTemp,Display, TEXT("overlap between %s and %s ended"),*Actor->GetName(),*OtherActor->GetName());

	//currentYaw = FMath::FInterpTo(currentYaw,targetYaw,DeltaTime,speed);

	auto doorRotation = GetOwner()->GetActorRotation();
	doorRotation.Yaw = currentYaw;
	GetOwner()->SetActorRotation(doorRotation);
}


void UDoorOpen::DoorHandling(float DeltaTime)
{
	if(EventDriven == false)
	{
		if(TriggerVolume->IsOverlappingActor(player))
		{
			currentYaw = FMath::FInterpTo(currentYaw,targetYaw,DeltaTime,speed);
			auto rotate = GetOwner()->GetActorRotation();
			rotate.Yaw = currentYaw;
			GetOwner()->SetActorRotation(rotate);
		}
		else
		{
			currentYaw = FMath::FInterpTo(currentYaw,initialYaw,DeltaTime,speed);
			auto rotate = GetOwner()->GetActorRotation();
			rotate.Yaw = currentYaw;
			GetOwner()->SetActorRotation(rotate);
		}
	}
}